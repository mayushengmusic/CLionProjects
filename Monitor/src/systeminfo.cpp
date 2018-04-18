//
// Created by jaken on 18-4-1.
//

#include <iostream>
#include "include/systeminfo.hpp"


systeminfo::systeminfo() : exc(){
}

const int systeminfo::getcpu() noexcept {
    try{
        std::string results;
        if (exc.ProcessSingleCmd("cpu.sh", results) != 0)
            return -1;
        std::stringstream ss;
        std::vector<int> sampling;

        ss << results;
        while (!ss.eof()) {
            int value = 0;
            ss >> value;
            if(value!=0)
                sampling.push_back(value);
        }
        if(sampling.empty())
            return -1;

        return 100 - std::accumulate(sampling.begin(),
                               sampling.end(), 0) / int(sampling.size());
    }catch (...){

        LOG(ERROR)<<"getcpu happend some error ";
        return -1;
    }
}

const int systeminfo::getmemery() noexcept {
    try {
        std::string results;
        exc.ProcessSingleCmd("memery.sh",results);

        return atoi(results.c_str());
    }catch (...){
        LOG(ERROR)<<"getmemery happend some error";
    }
    return -1;
}

const std::string systeminfo::getzpoolstatus() noexcept {
    try{
        std::string results;
        exc.ProcessSingleCmd("zpoolstatus.sh",results);
        return results;
    }catch (...){
        LOG(ERROR)<<"getzpoolstatus happend some error";
    }
    return std::string();
}

const int systeminfo::getnetspeeddown() noexcept {
    try{
        std::string results;
        exc.ProcessSingleCmd("netspeeddown.sh",results);
        return atoi(results.c_str());
    }catch (...){
        LOG(ERROR)<<"getnetspeeddown happend some error";
    }
    return -1;
}

const int systeminfo::getnetspeedup() noexcept {
    try{
        std::string results;
        exc.ProcessSingleCmd("netspeedup.sh",results);
        return atoi(results.c_str());
    }catch (...){
        LOG(ERROR)<<"getnetspeedup happend some error";
    }
    return -1;
}

const std::string systeminfo::getlocip() noexcept {
    try{
        std::string results;
        exc.ProcessSingleCmd("locip.sh",results);
        if(!results.empty()) {

            return results;
        }
    }catch (...)
    {
        LOG(ERROR)<<"getlocip happend some error";
    }
    return "0.0.0.0";
}

const std::string systeminfo::getpubip() noexcept {
    try{
        std::string results;
        exc.ProcessSingleCmd("pubip.sh",results);
        if(!results.empty()) {
            return results;
        }
    }catch (...)
    {
        LOG(ERROR)<<"getpubip happend some error";
    }
    return "0.0.0.0";
}