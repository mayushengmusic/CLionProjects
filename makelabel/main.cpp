#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <dirent.h>
#include <cstring>
#include <fstream>
#include <regex>



int main(int argc,char **argv) {



    std::string MainPath("/home/jaken/PIC/sexy");
    DIR *MainPathDir = opendir(MainPath.c_str());
    if(MainPathDir==NULL)
    {
        std::cerr<<"cannot open the directory"<<std::endl;

        return 1;
    }

    std::string currentPath;
    std::vector<std::string> FileCollect;
    std::queue<std::string> PathQueue;
    PathQueue.push(MainPath);

    while(!PathQueue.empty())
    {
        currentPath=PathQueue.front();
        PathQueue.pop();


        DIR *currentPathDir=opendir(currentPath.c_str());

        struct dirent * leap = readdir(currentPathDir);
        while(leap)
        {
            std::regex jpg(".*\\.jpg$");
            std::string name(leap->d_name);

            if(std::regex_match(name,jpg))
            {
                std::string path = currentPath+std::string("/")+std::string(leap->d_name);

                FileCollect.push_back(path);

            }
            else
            {
                if(strcmp(leap->d_name,".")!=0 && strcmp(leap->d_name,"..")!=0)
                {
                    std::string path = currentPath+std::string("/")+std::string(leap->d_name);
                    PathQueue.push(path);
                }

            }


            leap = readdir(currentPathDir);

        }



    }



    std::fstream trainlable("./train.txt",std::ios_base::out|std::ios_base::app);
    std::fstream testlable("./test.txt",std::ios_base::out|std::ios_base::app);

    int i=0;

    std::regex split("/home/jaken/PIC/(.*)$");

    for(auto x: FileCollect)
    {
        std::smatch m;
        std::regex_match(x,m,split);
        trainlable<<m[1]<<" "<<1<<std::endl;
        i++;
        if(i==90000)
            break;
    }

    for(auto x: FileCollect)
    {
        std::smatch m;
        std::regex_match(x,m,split);
        testlable<<m[1]<<" "<<1<<std::endl;
        i++;
        if(i==98000)
            break;
    }




    return 0;
}