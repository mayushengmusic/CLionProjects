//
// Created by jaken on 18-2-13.
//


#ifndef GOSEND_READCOMMAND_HPP
#define GOSEND_READCOMMAND_HPP
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

void readcommand(std::string & data){

    json json_data;

    while(std::cin.good())
    {
        std::string key,value;
        std::getline(std::cin,key);
        std::getline(std::cin,value);
        if(!key.empty()&&!value.empty())
        json_data[key] = value;
    }

    data = json_data.dump();
}
#endif //GOSEND_READCOMMAND_HPP
