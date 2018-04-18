//
// Created by jaken on 16-12-5.
//
#include <thread>
#include <iostream>
#include <exception>
#ifndef PARALLELS_SCOPED_THREAD_HPP
#define PARALLELS_SCOPED_THREAD_HPP
class scoped_thread{
private:
    std::thread t;
public:
    explicit scoped_thread(std::thread t_):t(std::move(t_)){
        if(!t.joinable())
            throw std::logic_error("NO THREAD");
    }

    ~scoped_thread(){t.join();}
    scoped_thread(scoped_thread const &)= delete;
    scoped_thread & operator=(scoped_thread const &)= delete;

};


#endif //PARALLELS_SCOPED_THREAD_HPP
