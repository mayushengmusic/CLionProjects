//
// Created by Jaken on 2018/1/10.
//

#ifndef BLOCKCHAINDEMO_NETSERVICE_HPP
#define BLOCKCHAINDEMO_NETSERVICE_HPP

#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "block.pb.h"


namespace net {

    enum {
        PORT = 20000, PRE_SIZE = 17, STATUS_SIZE=3
    };

    using namespace boost::asio;


    class tx_session :
            public boost::enable_shared_from_this<tx_session> {
    public:
        explicit tx_session(io_context &context) :
                sock(context) {
        }


        void start() {
            do_handle();
        }

        ip::tcp::socket &get_sock() {
            return sock;
        }

    private:

        void do_handle() {
            auto self(shared_from_this());
            boost::shared_ptr<std::string> size_buf_ptr(new std::string(PRE_SIZE, '\0'));
            async_read(sock, buffer(*size_buf_ptr), transfer_exactly(PRE_SIZE),
                       [this, size_buf_ptr, self]//this for using sock
                       (const boost::system::error_code &ec, size_t bytes) {

                           std::cout << ec << " 1 " << bytes << std::endl;
                           char *end;
                           long data_size = std::strtol(size_buf_ptr->c_str(), &end, 10);
                           boost::shared_ptr<std::string> data_buf_ptr(new std::string(data_size + 1, '\0'));
                           async_read(sock, buffer(*data_buf_ptr), transfer_all(), [this, data_buf_ptr, self]
                           (const boost::system::error_code &ec, size_t bytes) {

                               std::cout << ec << " 2 " << bytes << std::endl;
                               std::cout << "recv: " << *data_buf_ptr << std::endl;

                           }
                           );
                       }
            );
        }

        ip::tcp::socket sock;
    };


    class server {
    public:
        explicit server(io_context &context)
                : accep(context, ip::tcp::endpoint(ip::tcp::v4(), net::PORT)) {
            do_accept();
        }


    private:

        void do_accept() {
            boost::shared_ptr<tx_session> one_tx_session_ptr(new tx_session(accep.get_executor().context()));
            accep.async_accept(one_tx_session_ptr->get_sock(), [this, one_tx_session_ptr](
                    const boost::system::error_code &ec
            ) {
                one_tx_session_ptr->start();
                std::cout << ec<<"ec"<< std::endl;
                do_accept();
            });

        }

        ip::tcp::acceptor accep;


    };

    class client {
        typedef ip::tcp::socket socket;
        typedef ip::tcp::endpoint endpoint;

    public:
        explicit client() : service(), dummy_work(new io_service::work(service)) {
            running_thread = std::thread([](io_service *service) {
                service->run();
            }, &service);
        }

        ~client() {
            service.stop();
            running_thread.join();
        }


        void async_send(std::string &data, const std::string &addr) {

            boost::shared_ptr<socket> sock_ptr(new socket(service));
            sock_ptr->connect(endpoint(ip::address_v4::from_string(addr), PORT));
            boost::shared_ptr<std::string> data_ptr(new std::string(data));
            boost::shared_ptr<std::string> size_ptr(new std::string(std::to_string(data.size())));
            size_ptr->resize(PRE_SIZE, '\0');

            async_write(*sock_ptr, buffer(*size_ptr), transfer_exactly(PRE_SIZE), [sock_ptr, data_ptr, size_ptr]
                    (const boost::system::error_code &ec, size_t bytes) {
                std::cout << ec << " " << bytes << std::endl;

                async_write(*sock_ptr, buffer(*data_ptr), transfer_all(), [sock_ptr, data_ptr](
                        const boost::system::error_code &ec, size_t bytes
                ) {
                    std::cout << ec << " " << bytes << std::endl;
                    boost::shared_ptr<std::string> status_ptr(new std::string());
                    status_ptr->resize(STATUS_SIZE, '\0');


                });
            });

        }

    private:

        io_service service;
        boost::shared_ptr<io_service::work> dummy_work;
        std::thread running_thread;

    };


}


#endif //BLOCKCHAINDEMO_NETSERVICE_HPP
