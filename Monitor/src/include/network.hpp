//
// Created by jaken on 18-4-2.
//

#ifndef MONITOR_NETWORK_HPP
#define MONITOR_NETWORK_HPP
#include <boost/asio.hpp>

namespace ba = boost::asio;


class network{
public:
    network():icx(),sock(icx),resolver(icx){
    }
    network(network&) = delete;
    network(network&&) = delete;
    int exchangedatawithserver(const std::string &req,std::string &res) noexcept ;
private:
    ba::io_context icx;
    ba::ip::tcp::socket sock;
    ba::ip::tcp::resolver resolver;
};

#endif //MONITOR_NETWORK_HPP
