//
// Created by jaken on 16-12-3.
//
#include <iostream>
#include <thread>
#ifndef PARALLELS_THREAD_GURAD_HPP
#define PARALLELS_THREAD_GURAD_HPP
class thread_guard{
    std::thread & t;
public:
    explicit thread_guard(std::thread & t_):t(t_){};
    ~thread_guard(){
        if(t.joinable())
        {
            t.join();
        }
    }
    thread_guard(const thread_guard &)= delete;
    thread_guard&operator=(const thread_guard &) = delete;
};

#endif //PARALLELS_THREAD_GURAD_HPP
