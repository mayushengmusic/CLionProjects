#include "watchman.hpp"

int main() {

    try{
        watchman test;
        test.addwatchfile("/tmp/dhcp.leases");
        //test.addwatchfile("/home/jaken/Lab/test.txt");
        test.updatedns();
    }catch (std::exception & e)
    {
        std::cout<<e.what()<<std::endl;
    }



    return 0;
}