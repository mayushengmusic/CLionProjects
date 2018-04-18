#include <iostream>
#include <thread>
#include "SERVER/udpserver.hpp"
int main() {
    udpserver test(12345);


    std::this_thread::sleep_for(std::chrono::seconds(1000));

    return 0;
}