//
// Created by jaken on 16-12-8.
//
#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#ifndef PARALLELS_SAFESTACK_HPP
#define PARALLELS_SAFESTACK_HPP

template<typename T>
class threadsafe_stack{
public:
    threadsafe_stack(){}
    threadsafe_stack(const threadsafe_stack & other);
    threadsafe_stack &operator=(const threadsafe_stack &) = delete;
    void push(T new_value);
    std::shared_ptr<T> pop();
    void pop(T & value);
    bool empty() const;

private:
    std::stack<T> data;
    mutable std::mutex m;
};


template<typename T>
threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack &other) {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
}

template<typename T>
void threadsafe_stack<T>::push(T new_value) {
    std::lock_guard<std::mutex> lock(m);
    data.push(new_value);
}

template<typename T>
std::shared_ptr<T> threadsafe_stack<T>::pop() {
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw std::out_of_range("sorry,I am empty");
    std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
    data.pop();
    return res;
}

template<typename T>
void threadsafe_stack<T>::pop(T &value) {
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw std::out_of_range("sorry,I am empty");
        value=data.top();
    data.pop();
}

template<typename T>
bool threadsafe_stack<T>::empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
}




#endif //PARALLELS_SAFESTACK_HPP
