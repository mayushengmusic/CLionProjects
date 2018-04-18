#include "huawei.hpp"


int main(){

    imat test;



    for(int i=0;i<50;++i)
    {
        std::vector<int> temp;
        for(int k=0;k<2;k++)
            temp.push_back(2*(i%7)*(i%7)+3);
        test.push_back(temp);

    }

   auto x= forecast(test,7);
    for(auto e: x)
    {
        std::cout<<e<<std::endl;
    }

    return 0;

}