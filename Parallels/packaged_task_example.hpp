//
// Created by jaken on 16-12-21.
//
#include <deque>
#include <mutex>
#include <future>
#include <thread>
#include <utility>
#include <iostream>
#include <vector>
#ifndef PARALLELS_PACKAGED_TASK_EXAMPLE_HPP
#define PARALLELS_PACKAGED_TASK_EXAMPLE_HPP
std::mutex m;
std::deque<std::packaged_task<void(int)>> tasks;
int timex=100;

std::future<void> productor(std::function<void(int)> f)
{
    std::packaged_task<void(int)> task(f);
    std::future<void> res=task.get_future();
    std::lock_guard<std::mutex> lk(m);
    tasks.push_back(std::move(task));
    return res;
}

void threadconsumer()
{
    int a=0;
    std::packaged_task<void(int)> task;
    while(true)
    {
        std::lock_guard<std::mutex> lk(m);
        if(tasks.empty())
            continue;
        task = std::move(tasks.front());
        tasks.pop_front();
        a++;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        task(a);
        if(a==timex)
            break;
    }

}

void threadproduct()
{
    auto func=[](int x){
        std::cout<<" task packets "<<x<<std::endl;
    };
    for(int i=0;i<timex;i++)
    {
        auto futurex = productor(func);
        futurex.wait();
        std::cout<<"wait....\n";
    }
}

#endif //PARALLELS_PACKAGED_TASK_EXAMPLE_HPP
