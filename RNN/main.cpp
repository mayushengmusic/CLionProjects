#include "lstm.hpp"


void int2str(int a,int b,rnn &lstm){

    arr inp(8,vec(2,0.0));
    auto c = a+b;

    for(int i=0;i<7;++i){
        inp[i][0]=double(a%2);
        inp[i][1]=double(b%2);
        a=a/2;
        b=b/2;
    }



    arr lab(8,vec(1,0.0));


    for(int i=0;i<7;++i){
        lab[i][0]=double(c%2);
        c=c/2;
    }



    lstm.backforward(inp,lab);


}


void trainning(rnn & lstm){
    static std::random_device gen;
    int a = gen()%64;
    int b = gen()%64;

    int2str(a,b,lstm);

}




int main() {


    rnn lstm(1,2,32,8);

    for(int i=0;i<INTER;++i)
    {
        trainning(lstm);

    }

    int a = 32;
    int b = 32;

    arr inp(8,vec(2,0.0));

    for(int i=0;i<7;++i){
        inp[i][0]=double(a%2);
        inp[i][1]=double(b%2);
        a=a/2;
        b=b/2;
    }

    show(inp);

    arr out;


    lstm.forward(inp,out);

    show(out);





/*
    imat test;

    for (int i = 0; i < 8; ++i) {
        std::vector<int> temp;
        for (int k = 0; k < 1; k++)
            temp.push_back((i)%7);
        test.push_back(temp);

    }

    auto x = forecast(test, 0, 3);
    for (auto e: x) {
        std::cout << e << std::endl;
    }
*/

/*

    rnn lstm(1,1,100,3);
    arr input{{0.1},{0.2},{0.3}};
    arr label{{0.1},{0.3},{0.6}};
    for(int i=0;i<INTER;++i) {
        lstm.backforward(input, label);
        if(i%EPOLL==0)
        LEARNNINGRATE=LEARNNINGRATE*DESC;
    }


    arr out;
    arr in{{0.1},{0.2},{0.3}};
    lstm.forward(in,out);

    for(auto &y: out)
        for(auto &x: y)
            std::cout<<x<<" ";


*/


    return 0;

}