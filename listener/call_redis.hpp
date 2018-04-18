//
// Created by jaken on 18-2-15.
//

#ifndef LISTENER_CALL_REDIS_HPP
#define LISTENER_CALL_REDIS_HPP
#include <cpp_redis/cpp_redis>
#include <glog/logging.h>
class write_redis{
public:
    explicit write_redis(){
        client.connect("127.0.0.1", 6379, [](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
            if (status != cpp_redis::client::connect_state::dropped) {
                LOG(INFO)<<"redis cpp connect ok";
            }
            else{
                LOG(FATAL)<<"redis cpp connect server fail";
            }
        });
        client.sync_commit();
    }

    write_redis(const write_redis &)= delete;
    write_redis(const write_redis &&)= delete;
    const write_redis &operator=(const write_redis &)= delete;
    const write_redis &operator=(const write_redis &&)= delete;

    void operator()(std::string &key,std::string &value){

        if(!client.is_connected())
        {
            client.connect("127.0.0.1", 6379, [](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
                if (status != cpp_redis::client::connect_state::dropped) {
                    LOG(INFO)<<"redis cpp reconnect ok";
                }
                else{
                    LOG(FATAL)<<"redis cpp reconnect server fail";
                }
            });
        }


        client.set(key, value, [](cpp_redis::reply& reply) {
            if(reply.is_error())
                LOG(WARNING)<<"write redis happened a error";
        });

        client.commit();
    }
private:
    cpp_redis::client client;

};
#endif //LISTENER_CALL_REDIS_HPP
