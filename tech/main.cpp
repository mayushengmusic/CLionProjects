#include <iostream>

class test{
public:
    void operator()(int x){
        std::cout<<"hello,world"<<std::endl;
    }

};

int main(){

    test one;
    one(3);

    return 0;
}