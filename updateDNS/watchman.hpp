//
// Created by jaken on 17-5-2.
//

#include <string>
#include <iostream>
#include <sys/inotify.h>
#include <unistd.h>
#include <fstream>
#include <regex>
#include "exception.hpp"
#include "mysqlconnectorc.hpp"
#include "parseconfig.hpp"
#ifndef UPDATEDNS_WATCHMAN_HPP
#define UPDATEDNS_WATCHMAN_HPP

class watchman{
public:
    watchman();
    void addwatchfile(const std::string & filepath);
    void updatedns();
    ~watchman(){
        close(inotifyfd);
    }

private:
    void syncwithmysql();
    static const uint BUFSIZE = 512;
    int inotifyfd;
    char buf[BUFSIZE];
    ssize_t numRead;
    std::string filepath;
    struct inotify_event *event;
    std::map<std::string,std::string> last_staus;
    static std::string mysqlurl;
    static std::string mysqluser;
    static std::string mysqlpasswd;
};

std::string watchman::mysqlurl=config_["mysqlurl"];
std::string watchman::mysqluser=config_["mysqluser"];
std::string watchman::mysqlpasswd=config_["mysqlpasswd"];

watchman::watchman():filepath(),last_staus(){
    inotifyfd=inotify_init();
    if(inotifyfd==-1)
        throw watchmanexception("inotifyfd_init() error\n");
    numRead=0;
    event=NULL;
    memset(buf,0,BUFSIZE);
    dns::mysqlconnector connector(mysqlurl,mysqluser,mysqlpasswd);
    if(!connector.excSQLwithoutReturn("update device set online = 0"))
    {
        close(inotifyfd);
        std::cerr<<"update data error\n";
        throw watchmanexception("database init error");
    }


}

void watchman::addwatchfile(const std::string &filepath) {
    int wd = inotify_add_watch(inotifyfd,filepath.c_str(),IN_MODIFY);
    if(wd==-1)
        throw watchmanexception("inotify_add_watch() error\n");
    this->filepath=filepath;
}

void watchman::updatedns() {

    syncwithmysql();

    static char *p;
    while(true)
    {
        numRead = read(inotifyfd,buf,BUFSIZE);
        if(numRead == 0) {
            std::cerr << "read() from inotify fd returned 0\n";
            continue;
        }
        if(numRead == -1)
        {
            close(inotifyfd);
            throw watchmanexception("read() error\n");
        }


        for(p=buf;p<buf+numRead;)
        {
            event = (struct inotify_event *) p;
            if(event->mask&IN_MODIFY)
            {
                std::cout<<"begin update"<<std::endl;
                syncwithmysql();
            }
            p+=sizeof(struct inotify_event)+event->len;
        }
    }
}

void watchman::syncwithmysql() {


        std::fstream filedata(filepath.c_str(),std::ios_base::in);
        char *linebuf;
        linebuf=new char[BUFSIZE];
        std::string mac;
        std::string ipv4;

        std::map<std::string,std::string> current_status;

        while(filedata.good())
        {
            memset(linebuf,0,BUFSIZE);
            filedata.getline(linebuf,BUFSIZE-1);
            std::string line(linebuf);
            if(line.empty())
                break;
            static std::regex r("[\\w]+\\s([\\w\\:]+)\\s([\\w\\.]+)\\s.+\\s[\\w\\:]+");
            static std::smatch m;
            if(!std::regex_match(line,m,r)) {
                std::cout<<line<<std::endl;
                delete[] linebuf;
                throw watchmanexception("please check /tmp/dhcp.leases\n");
            }
            mac = m[1];
            ipv4 = m[2];
            current_status[mac]=ipv4;
            if(last_staus[mac]==ipv4)
                continue;

            dns::mysqlconnector connector(mysqlurl,mysqluser,mysqlpasswd);

            std::string SQL="update device set online = 1,ipv4 = \"";
            SQL+=ipv4;
            SQL+="\"";
            SQL+=" where mac = \"";
            SQL+=mac;
            SQL+="\"";
            std::cout<<SQL<<std::endl;
            if(!connector.excSQLwithoutReturn(SQL))
            {
                std::cerr<<"update data error\n";
                continue;
            }

        }

        if(!last_staus.empty())
            for(auto & x: last_staus)
        {
            if(current_status.count(x.first)==0)
            {
                dns::mysqlconnector connector(mysqlurl,mysqluser,mysqlpasswd);
                std::string SQL="update device set online = 0";
                SQL+=" where mac = \"";
                SQL+=x.first;
                SQL+="\"";
                std::cout<<SQL<<std::endl;
                if(!connector.excSQLwithoutReturn(SQL))
                {
                    std::cerr<<"update data error\n";
                    continue;
                }
            }
        }

        last_staus = current_status;

}





#endif //UPDATEDNS_WATCHMAN_HPP
