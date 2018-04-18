//
// Created by jaken on 18-2-11.
//

#ifndef FUCKSOCK_CALLREDIS_HPP
#define FUCKSOCK_CALLREDIS_HPP
#include <cpp_redis/cpp_redis>
#include <iostream>


class callredis{
public:
    callredis(){
        cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);
        client_.connect("127.0.0.1", 6379, [](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
            if (status == cpp_redis::client::connect_state::dropped) {
                std::cerr << "client disconnected from " << host << ":" << port << std::endl;
            }
        });
        client_.sync_commit(std::chrono::milliseconds(100));
    }

    void operator()(std::string &json_data){
        if(!client_.is_connected())
        {
            client_.connect("127.0.0.1", 6379, [](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
                if (status == cpp_redis::client::connect_state::dropped) {
                    std::cerr << "client disconnected from " << host << ":" << port << std::endl;
                }
            });
        }

        client_.get("machine", [&json_data](cpp_redis::reply& reply) {
            std::cout << "get hello: " << reply << std::endl;
            if (reply.is_string())
              json_data=reply.as_string();
        });

        client_.sync_commit(std::chrono::milliseconds(100));

    }


private:

    cpp_redis::client client_;

};





#endif //FUCKSOCK_CALLREDIS_HPP
