#include <fstream>
#include "huawei.hpp"



int main() {




    std::ifstream file("/home/jaken/data.txt");


    imat test(45,ivec(5,0));

    for(int j=0;j<test.size();++j)
        for(int i=0;i<test[i].size();++i) {
            file >> test[j][i];


        }





  auto x = forecast(test,3,6);
    for(auto &z: x)
        std::cout<<" "<<z;

    std::cout<<std::endl;




/*
    adam test(1,1,3);
    mat a(3,vec(3));
    for(int i=0;i<3;++i)
        for(int j=0;j<3;++j)
            a[i][j]=myrand();

    a=test.getadamdelta_ua(a);

    show(a);

*/


    return 0;

}