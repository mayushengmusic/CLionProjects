//
// Created by Jaken on 2018/4/9.
//

#include "parsedns.hpp"
#include <memory>
#include <iostream>
#include "../DNS/message.h"
enum {max_length = 512};
void parsedns::parsedata(char *MessageCome, char *MessageBack, unsigned int MessageCome_lenth,
                         unsigned int &MessageBack_lenth){

    try {
        dns::Message querymessage;

        querymessage.decode(MessageCome,MessageCome_lenth);
        std::cout<<querymessage.asString()<<std::endl;
        querymessage.setQr(dns::Message::typeResponse);
        dns::ResourceRecord* rrA(new dns::ResourceRecord());
        rrA->setType(dns::RDATA_A);
        rrA->setClass(dns::CLASS_IN);
        rrA->setTtl(60);
        dns::RDataA* rdataA(new dns::RDataA());
        dns::uchar ip4[4]={};
        ip4[0]=dns::uchar(8);
        ip4[1]=dns::uchar(8);
        ip4[2]=dns::uchar(8);
        ip4[3]=dns::uchar(8);
        rdataA->setAddress(ip4);
        rrA->setName("mayusheng.cn");
        rrA->setRData(rdataA);
        querymessage.addAnswer(rrA);
        querymessage.encode(MessageBack,max_length,MessageBack_lenth);
    }catch (std::exception &e){
        std::cerr<<e.what()<<std::endl;
    }
}