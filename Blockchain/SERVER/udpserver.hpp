//
// Created by Jaken on 2018/4/9.
//

#ifndef BLOCKCHAIN_UDPSERVER_HPP
#define BLOCKCHAIN_UDPSERVER_HPP
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
namespace ba=boost::asio;
class udpserver {
public:

    explicit udpserver(short port);
    void do_receive();
    void do_send(size_t length);
    ~udpserver(){
        delete[] in_buffer;
        delete[] out_buffer;
    }

private:

    ba::io_context icx;
    ba::ip::udp::socket sock;
    ba::ip::udp::endpoint sender_endpoint;
    enum {max_length = 512};
    char* in_buffer;
    char* out_buffer;

};


#endif //BLOCKCHAIN_UDPSERVER_HPP
