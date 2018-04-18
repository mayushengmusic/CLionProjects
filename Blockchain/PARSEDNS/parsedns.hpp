//
// Created by Jaken on 2018/4/9.
//

#ifndef BLOCKCHAIN_PARSE_HPP
#define BLOCKCHAIN_PARSE_HPP


#include <string>

class parsedns {
public:
    parsedns()= default;
    void parsedata(char *MessageCome,char *MessageBack,unsigned int MessageCome_lenth,unsigned int &MessageBack_lenth);
};


#endif //BLOCKCHAIN_PARSE_HPP
