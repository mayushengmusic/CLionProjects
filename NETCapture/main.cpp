
#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <pcap.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <iostream>
#include <regex>

#include "MySqlWriter.hpp"
#include "CompBuf.hpp"
#include <memory.h>
#include "packet.hpp"

#define URL_MAX_LEN        2048

CompBuf buf;


void printlog(const std::string & message)
{
    time_t tt = time(NULL);
    tm* t= localtime(&tt);

    std::cout<<"date: "<<(t->tm_year+1900)<<"."<<(t->tm_mon+1)<<"."<<t->tm_mday<<"."<<t->tm_hour<<":"<<t->tm_min<<":"<<t->tm_sec<<" "<<message<<'\n';

}

/*convert unsigned long int to char* */
void typeConvert(unsigned long int number,std::string& str){
    std::stringstream ss;
    ss << number;
    str=ss.str();
}



void show_iphdr(struct iphdr *ip,struct packet * &myInfo)
{
    struct in_addr addr;
    addr.s_addr = ip->saddr;
    strcpy((myInfo)->srcip,inet_ntoa(addr));
    addr.s_addr = ip->daddr;
    strcpy((myInfo)->desip,inet_ntoa(addr));
}

int parse_http_head(const u_char *payload,struct packet *&myInfo)
{
    if(memcmp(payload, "GET ", 4)!=0) {

        return -1;
    }

    std::string myString = (char*)payload;
    std::string index,host;

    std::regex reg("^GET\\s+(.*?)\\s+HTTP/.*\\r\\n");
    std::regex reg2("Host\\s?:\\s+(.*?)\\r\\n");

    const std::sregex_iterator end;
    for(std::sregex_iterator iter(std::cbegin(myString),std::cend(myString),reg);
        iter != end; ++iter){
        index=(*iter)[1];
    }
    for(std::sregex_iterator iter(std::begin(myString),std::end(myString),reg2);
        iter != end; ++iter){
        host=(*iter)[1];
    }

    std::string myUrl="http://"+host+index;
    std::string infoType="HTTP";

    memset((myInfo)->comment,0,2048);
    strcpy((myInfo)->comment,myUrl.c_str());
    memset((myInfo)->type,0,8);
    strcpy((myInfo)->type,infoType.c_str());

    return 0;
}

int prase_packet(const u_char *buf,  int caplen,struct packet *&myInfo)
{
    uint16_t e_type;        //typedef unsigned short int	uint16_t;
    uint32_t offset;        //typedef unsigned int		uint32_t;
    const u_char *tcp_payload;  //typedef unsigned char u_char;

    /* ether header */
    struct ethhdr *eth = NULL;
    eth = (struct ethhdr *)buf;
    e_type = ntohs(eth->h_proto);
    offset = sizeof(struct ethhdr);

    /*vlan 802.1q*/
    while(e_type == ETH_P_8021Q) {
        e_type = (buf[offset+2] << 8) + buf[offset+3];
        offset += 4;
    }
    if (e_type != ETH_P_IP) {
        return -1;
    }

    /* ip header */
    struct iphdr *ip = (struct iphdr *)(buf + offset);
    e_type = ntohs(ip->protocol);
    offset += sizeof(struct iphdr);
    show_iphdr(ip,myInfo);  //fill the content of srcip and destip.

    if(ip->protocol ==IPPROTO_TCP) {
        /*tcp header*/
        struct tcphdr *tcp = (struct tcphdr *) (buf + offset);
        offset += (tcp->doff << 2);
        tcp_payload = (buf + offset);

        /*prase http header*/
        parse_http_head(tcp_payload,myInfo);

    }else if(ip->protocol == IPPROTO_UDP ){
        /*udp header*/
        struct udphdr *udp=(struct udphdr *)(buf + offset);
        int sport = ntohs(udp->source);
        int dport = ntohs(udp->dest);
        if (dport != 8000 || sport > 4100 || sport<4000) {

            return -1;
        }

        unsigned long int QQnumber=(unsigned long int )buf[49]*16*16*16*16*16*16 + buf[50]*16*16*16*16 + buf[51]*16*16 + buf[52];
        std::string infoType="OICQ";
        std::string infoComment;
        typeConvert(QQnumber,infoComment);  //convert unsigned long int to string.
        memset((myInfo)->type,0,8);
        strcpy((myInfo)->type,infoType.c_str());
        memset((myInfo)->comment,0,2048);
        strcpy((myInfo)->comment,infoComment.c_str());
    } else{

        return -1;
    }

    return 0;
}

void get_packet(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packetx)
{

    struct packet *myInfo=new packet;

    memset(myInfo,0,sizeof(struct packet));
    myInfo->next= nullptr;
    myInfo->size=pkthdr->len;
    prase_packet(packetx, pkthdr->len,myInfo);
    if(myInfo != nullptr) {

        buf.insertelem(myInfo);
    }else{
        delete myInfo;
        myInfo= nullptr;
    }
}

void writebythread()
{

    MySqlWriter *db = new MySqlWriter("tcp://10.0.3.16:3306","king","uestc305mysql","packetcapture");
    while(true)
    {
        struct packet * datep = buf.getelem();
        if(datep == nullptr)
        {
            printlog("Write thread go to sleep!");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        else
        {
            if(strcmp(datep->type,"")==0)
            {
                delete datep;

                continue;
            }
            printlog("Write thread try to write db!");
            bool check = db->tryToWriteData(datep);


            delete datep;

            if(!check)
            {
                printlog("DB Write error, Try to fix it!");
                delete db;
                db = new MySqlWriter("tcp://10.0.3.16:3306","king","uestc305mysql","packetcapture");

            }


        }

    }
    delete db;

}




int main(int argc,char **argv)
{

    if(argc!=2)
    {
        std::cout<<"command netdev"<<std::endl;
        return 1;
    }


    char errBuf[PCAP_ERRBUF_SIZE]; /*error Buff*/

    pcap_t *dev; /*network interface*/


    /*look up device network addr and mask*/

    char *devStr=argv[1];

    /*if(pcap_lookupnet(devStr, &netp, &maskp, errBuf)) {
        printf("get net failure\n");
        exit(1);
    }



    addr.s_addr = netp;
    net = inet_ntoa(addr);
    printf("network: %s\n", net);

    addr.s_addr = maskp;
    mask = inet_ntoa(addr);
    printf("mask: %s\n", mask);*/

    /*open network device for packet capture*/
    dev = pcap_open_live(devStr, 65536, 1, 0, errBuf);
    if(NULL == dev) {
        printf("Open %s failure, please check the device!\n", devStr);
        exit(1);
    }
    std::thread t1(writebythread);
    std::thread t2(writebythread);
    std::thread t3(writebythread);

    t1.detach();
    t2.detach();
    t3.detach();
    /*process packets from a live capture or savefile*/
    pcap_loop(dev, 0, get_packet, NULL);

    /*close device*/
    pcap_close(dev);

    return 0;
}