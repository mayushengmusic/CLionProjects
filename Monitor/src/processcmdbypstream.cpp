//
// Created by jaken on 18-4-2.
//
#include <future>
#include <iostream>
#include "include/processcmdbypstream.hpp"
#include <pstreams/pstream.h>
using namespace redi;

int processcmdbypstream(const std::string &cmd, std::string &results)
{
    results.clear();
    std::future<int> child=std::async(std::launch::async,
    [&cmd,&results]{
        const pstreams::pmode mode=pstreams::pstderr|pstreams::pstdout;
        ipstream in(cmd,mode);
        std::string str;
        while(in>>str){
            results+=str+=' ';
        }
        std::cout<<in.get()<<std::endl;
        if(results.empty())
            return in.get();
        while(results.back()=='\n'||results.back()==' ')
            results.pop_back();
        return in.get();
    });


    if(child.wait_for(std::chrono::seconds(WAIT_MINUTES))==std::future_status::ready)
    {
        return child.get();
    }

    return -1;
}