//
// Created by jaken on 18-4-2.
//

#include "include/network.hpp"
#include <glog/logging.h>
#include <iostream>

#define SERVER_HOST "www.google.com"
#define PORT "80"
int network::exchangedatawithserver(const std::string &req, std::string &res) noexcept {
    if(req.empty())
    {
        LOG(INFO)<<"a empty request happend";
        return -1;
    }
    try {
        ba::connect(sock, resolver.resolve(SERVER_HOST, PORT));
        ba::write(sock, boost::asio::buffer(req, req.size()));
        size_t reply_length = 0;
        sock.wait(sock.wait_read);
        do {
            std::string temp(sock.available() + 1, '\0');
            reply_length = boost::asio::read(sock, boost::asio::buffer(temp, temp.size() - 1));
            res += temp;
        } while (reply_length > 0);

        if(reply_length!=0)
            return -2;
        return 0;

    }catch (...)
    {
        LOG(WARNING)<<"some error happend,please check server and network";
    }
    return -3;
}