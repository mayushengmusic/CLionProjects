//
// Created by jaken on 18-2-13.
//

#ifndef LISTENER_NETWORK_HPP
#define LISTENER_NETWORK_HPP
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <glog/logging.h>
#include "sha256.hpp"
#include "call_redis.hpp"
#include "setmap.hpp"
#include "json.hpp"

using namespace boost::asio;
using json = nlohmann::json;

void fail(boost::system::error_code ec,const char *what){
    LOG(WARNING)<<ec<<" : "<<what;
}

class session:public boost::enable_shared_from_this<session>{
public:
    explicit session(io_context &context,std::shared_ptr<write_redis>& redis,std::shared_ptr<fliter> &fliter)
            :sock_(context),size_(),buffer_(),status_{'\0'},redis_ptr(redis),fliter_ptr(fliter){
    }

    void start(){
        size_.resize(PRE_SIZE,'\0');
        async_read(sock_,buffer(size_),transfer_exactly(4),boost::bind(&session::on_read_size,shared_from_this(),
                                                            boost::placeholders::_1,boost::placeholders::_2));
    }

    inline ip::tcp::socket & get_sock() noexcept {
        return sock_;
    }

private:
    void on_read_size(boost::system::error_code ec,size_t bytes){
        boost::ignore_unused(bytes);
        if(ec)
            return fail(ec,"on read size");
        auto data_size = std::atol(size_.c_str());
        buffer_.resize(data_size,'\0');
        async_read(sock_,buffer(buffer_),transfer_exactly(data_size),boost::bind(&session::on_read,shared_from_this(),
                                                                       boost::placeholders::_1,boost::placeholders::_2));


    }

    void on_read(boost::system::error_code ec,size_t bytes){

        boost::ignore_unused(bytes);
        if(ec)
            return fail(ec,"on read");


            std::string sha256_ = buffer_.substr(0, SHA256_SIZE);
            std::string json_data = buffer_.substr(SHA256_SIZE, buffer_.size() - SHA256_SIZE);



            if (sha256(json_data) == sha256_) {
                status_[0] = 'O';
                status_[1] = 'K';
                status_[2] = '\0';
                try {
                    json js = json::parse(json_data);
                    std::string id_index = js.at("id");
                    if(!id_index.empty()) {
                        (*redis_ptr)(id_index, json_data);
                        fliter_ptr->check_write_file(id_index);
                    }
                }catch (...)
                {
                    status_[0] = 'N';
                    status_[1] = '0';
                    status_[2] = '\0';
                    LOG(WARNING)<<"some error happened on update fliter and write redis";
                }
            } else {
                status_[0] = 'N';
                status_[1] = '0';
                status_[2] = '\0';
            }

        async_write(sock_,buffer(status_,STATUS_SIZE),transfer_all(),boost::bind(&session::on_write,shared_from_this(),
        boost::placeholders::_1,boost::placeholders::_2));



    }

    void on_write(boost::system::error_code ec,size_t bytes){
        if(ec)
            return fail(ec,"on write");
        sock_.close();
    }

    enum{
        PRE_SIZE = 4,
        STATUS_SIZE = 3,
        SHA256_SIZE = 64
    };
    ip::tcp::socket sock_;
    std::string size_;
    std::string buffer_;
    std::shared_ptr<write_redis> redis_ptr;
    std::shared_ptr<fliter> fliter_ptr;
    char status_[STATUS_SIZE];
};


class server {
public:
    explicit server(io_context &context,std::shared_ptr<write_redis>& redis,std::shared_ptr<fliter> &fliter)
            : accep(context, ip::tcp::endpoint(ip::tcp::v4(), PORT)),redis_ptr(redis),fliter_ptr(fliter) {
        do_accept();
    }


private:

    void do_accept() {
        boost::shared_ptr<session> session_ptr(new session(accep.get_executor().context(),redis_ptr,fliter_ptr));
        accep.async_accept(session_ptr->get_sock(), [this, session_ptr](
                const boost::system::error_code &ec
        ) {
            if(ec)
                return fail(ec,"on accept");
            session_ptr->start();
            do_accept();
        });

    }
    enum {
        PORT = 12321
    };
    ip::tcp::acceptor accep;
    std::shared_ptr<write_redis> redis_ptr;
    std::shared_ptr<fliter> fliter_ptr;


};

#endif //LISTENER_NETWORK_HPP
