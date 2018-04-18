#include "network.hpp"
#include "readcommand.hpp"
#include "sha256.hpp"
int main(int argc, char * argv[]) {


    google::InitGoogleLogging(argv[0]);
    std::string data;
    io_service service;
    boost::shared_ptr<net_cli> ptr(new net_cli(service));
    readcommand(data);
    data = sha256(data)+data;
    ptr->send_data(data);
    std::future<bool> future = std::async(std::launch::async,[&service](){

        service.run();
        return true;
    });


    if(future.wait_for(std::chrono::seconds(10))!=std::future_status::ready) {
        ptr->clear();
        service.stop();
        LOG(INFO) << "send data for a log time";
    }
    return 0;


}