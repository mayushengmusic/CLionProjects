//
// Created by Jaken on 2018/4/9.
//

#include "udpserver.hpp"
#include "../PARSEDNS/parsedns.hpp"
udpserver::udpserver(short port):icx(),
sock(icx,ba::ip::udp::endpoint(ba::ip::udp::v4(),port)),
in_buffer(new char[max_length]),out_buffer(new char[max_length])
{
    auto func = [](ba::io_context *icx){
        ba::executor_work_guard<ba::io_context::executor_type> run
                = boost::asio::make_work_guard(*icx);
        icx->run();
    };

    std::thread t1(func,&icx);
    t1.detach();

    do_receive();

}

void udpserver::do_receive() {

    sock.async_receive_from(ba::buffer(in_buffer,max_length),sender_endpoint,
                            [this](const boost::system::error_code &ec,size_t bytes_recvd){
                                if(!ec&&bytes_recvd>0)
                                {
                                    static parsedns parse;
                                    u_int size=0;
                                    parse.parsedata(in_buffer,out_buffer,(u_int)bytes_recvd,size);
                                    if(size!=0) {
                                        do_send((size_t)size);
                                    }else{
                                        do_receive();
                                    }
                                } else{
                                    do_receive();
                                }
                            });
}

void udpserver::do_send(size_t length){
    sock.async_send_to(
            ba::buffer(out_buffer,length),sender_endpoint,
            [this](const boost::system::error_code,size_t){
                do_receive();
            }
    );

}