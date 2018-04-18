#include "netservice.hpp"
#include "SHA256.hpp"
#include "ecdsa.hpp"
using namespace boost::asio;
typedef CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey private_key;


bool  elect(private_key &privateKey,const std::string &random,float rates,unsigned int &times)
{
    unsigned long rate_mum = std::numeric_limits<unsigned long>::max();
    unsigned long rate_son = (u_long)(rate_mum*rates);
    CryptoPP::Integer rate_mum_Interger(std::to_string(rate_mum).c_str());
    CryptoPP::Integer rate_son_Interger(std::to_string(rate_son).c_str());
    unsigned int time = 1;
    std::string signature;
    sign_message(privateKey,random,signature);
    std::string data = sha256(signature);
    CryptoPP::Integer data_Interger(data.c_str());
    CryptoPP::Integer base;
    base.Power2(64);


    if(data_Interger*rate_mum<=base* rate_son)
        return true;

    while(time!=0)
    {
        data = sha256(data);
        CryptoPP::Integer data_Interger_tmp(data.c_str());
        if(data_Interger_tmp*rate_mum<=base* rate_son)
            return true;
    }


return false;
}



int main(){

    std::thread t1([](){

        io_context context;
        net::server server(context);
        context.run();
    });

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::thread t2([](){
        net::client worker;
        for(int i=0;i<30;++i) {
            std::string data("hello,world");
            worker.async_send(data, std::string("127.0.0.1"));
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    });

   std::thread t3([](){
        net::client worker;
        for(int i=0;i<30;++i) {
            std::string data("hello,world");
            worker.async_send(data, std::string("127.0.0.1"));
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    });



    t1.join();
    t2.join();
    t3.join();


    return 0;
}