//
// Created by jaken on 17-5-2.
//
#include<exception>
#include<string>
#ifndef UPDATEDNS_EXCEPTION_HPP
#define UPDATEDNS_EXCEPTION_HPP
class watchmanexception:public std::exception{
public:
    watchmanexception(const std::string & message):E_MSG(message){

    }
    virtual const char * what() const noexcept override {
        return E_MSG.c_str();
    }


private:
    std::string E_MSG;
};


#endif //UPDATEDNS_EXCEPTION_HPP
