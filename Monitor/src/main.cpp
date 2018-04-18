#include <iostream>

#include <glog/logging.h>
#include "include/processcmdbypstream.hpp"
#include <iostream>

int main(int argc,char **argv) {
    google::InitGoogleLogging(argv[0]);
    std::string results="xxx";
    std::string cmd("echo \"hello world \n hello c++\"");
    std::cout<<processcmdbypstream(cmd,results)<<std::endl;
    std::cout<<results;



    return 0;
}