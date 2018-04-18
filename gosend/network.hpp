//
// Created by jaken on 18-2-13.
//

#ifndef GOSEND_NETWORK_H
#define GOSEND_NETWORK_H
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <boost/concept_check.hpp>
#include <glog/logging.h>

using namespace boost::asio;

void
fail(boost::system::error_code ec, char const* what)
{
    LOG(WARNING) << what << ": " << ec.message();
}

class net_cli:public boost::enable_shared_from_this<net_cli>{
public:
    explicit net_cli(io_service &service_):socket_(service_),resolver_(service_),
    data_(),host("listen.mayusheng.cn"),port("12321"),status_{'\0'}{

    }

    void send_data(const std::string &data){
        data_=data;
        size_ = std::to_string(data.size());
        socket_.open(ip::tcp::v4());
        resolver_.async_resolve(host, port, boost::bind(&net_cli::on_resolve, shared_from_this(),
                                                        boost::placeholders::_1, boost::placeholders::_2));
    }

    void clear(){
        socket_.cancel();
        socket_.close();
    }

private:

    void on_resolve(boost::system::error_code ec,ip::tcp::resolver::results_type results){
        if(ec) {
            socket_.close();
            return fail(ec, "resolve");
        }

        async_connect(socket_,results.begin(),results.end(),
        boost::bind(&net_cli::on_connect,shared_from_this(),boost::placeholders::_1));
    }

    void on_connect(boost::system::error_code ec)
    {
       if(ec) {
           socket_.close();
           return fail(ec, "connect");
       }
        if(size_.size()<=PRE_SIZE)
            size_.resize(PRE_SIZE,'\0');
        else
            LOG(FATAL)<<"data size is to large";

        async_write(socket_,buffer(size_),transfer_exactly(PRE_SIZE),
                    boost::bind(&net_cli::on_write_size,shared_from_this(),boost::placeholders::_1,boost::placeholders::_2));

    }

    void on_write_size(boost::system::error_code ec,size_t bytes){
        boost::ignore_unused_variable_warning(bytes);
        if(ec) {
            socket_.close();
            return fail(ec, "on write size");
        }
        async_write(socket_,buffer(data_),transfer_all(),
                    boost::bind(&net_cli::on_write,shared_from_this(),boost::placeholders::_1,boost::placeholders::_2));

    }

    void on_write(boost::system::error_code ec,std::size_t bytes){
        boost::ignore_unused_variable_warning(bytes);
        if(ec) {
            socket_.close();
            return fail(ec, "write");
        }
        memset(status_,STATUS_SIZE,'\0');
        async_read(socket_,buffer(status_,STATUS_SIZE),transfer_all(),
        boost::bind(&net_cli::on_read,shared_from_this(),boost::placeholders::_1,boost::placeholders::_2));
    }

    void on_read(boost::system::error_code ec,std::size_t bytes){
        boost::ignore_unused_variable_warning(bytes);
        if(ec) {
            socket_.close();
            return fail(ec, "read");
        }
        socket_.close();
        LOG(INFO)<<"server check status: "<<status_;
    }

private:

    enum {
        PRE_SIZE = 4,
        SHA_SIZE = 64,
        STATUS_SIZE = 3
    };
    std::string host;
    std::string port;
    ip::tcp::socket socket_;
    ip::tcp::resolver resolver_;
    std::string data_;
    std::string size_;
    char status_[STATUS_SIZE];
};
#endif //GOSEND_NETWORK_H
