//
// Created by jaken on 16-12-13.
//
#include <iostream>
#include <mutex>
#include <thread>
#include <exception>
#include <climits>
#ifndef PARALLELS_HIERARCHICAL_MUTEX_H
#define PARALLELS_HIERARCHICAL_MUTEX_H
class hierarchical_mutex
{
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;

    void check_for_hierarchy_violation()
    {
        if(this_thread_hierarchy_value<=hierarchy_value)
        {
            throw std::logic_error("mutex hierarchy violated");
        }

    }

    void update_hierarchy_value()
    {
        previous_hierarchy_value=this_thread_hierarchy_value;
        this_thread_hierarchy_value=hierarchy_value;
    }

public:
    explicit hierarchical_mutex(unsigned long value):hierarchy_value(value),previous_hierarchy_value(0){}
    void lock()
    {
        check_for_hierarchy_violation();
        internal_mutex.lock();
    }
    void unlock()
    {
        this_thread_hierarchy_value=previous_hierarchy_value;
        internal_mutex.unlock();
    }
    bool try_lock()
    {
        check_for_hierarchy_violation();
        if(!internal_mutex.try_lock())
            return false;
        update_hierarchy_value();
        return true;
    }
};


thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);
#endif //PARALLELS_HIERARCHICAL_MUTEX_H
