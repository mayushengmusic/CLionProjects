#include <iostream>
#include "API/ITask.hpp"

class A{
public:
    A(){
        std::cout<<"created "<<std::endl;
    }
    virtual ~A(){
        std::cout<<"destroyed "<<std::endl;
    }
};

int work()
{
    std::string * ptr = new std::string("hello world");
}


int main() {

    std::string * ptr = new std::string("hello");
    delete ptr;
    return 0;
}