#include <iostream>
#include <random>
#include "SHA256.hpp"
#include "ecdsa.hpp"

typedef CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey pri_key;
typedef CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pub_key;
typedef CryptoPP::Integer bignum;


int worker() {

    std::random_device gen;
    std::string rand(sha256(std::to_string(gen())));
    u_int times = 100;


    std::vector<u_int> amounts(times,0);

    bignum sum=0;

    for(u_int i=0;i<times;++i)
    {
        amounts[i]=gen();
        sum+=amounts[i];
    }

    bignum base;
    base = base.Power2(256);
    int index=0;
    std::cout<<"all of the money: "<<sum<<std::endl;
    std::cout<<"base: "<<base<<std::endl;

    for(u_int i=0;i<times;++i)
    {
        pri_key pr_key;
        generate_privatekey(pr_key);
        pub_key pu_key;
        make_publickey(pr_key,pu_key);
        static std::string signature;
        signature="";
        sign_message(pr_key,rand,signature);
        bignum frac((sha256(signature)+"h").c_str());
        if(frac*sum<=base*amounts[i]) {
            std::cout <<amounts[i] << " " << sha256(signature) << std::endl;
            index++;
        }



    }


    return index;
}

int main(){
    std::vector<int> ans(100,0);
    for(int i=0;i<100;++i)
    {
        ans[worker()]++;
    }

    for(int i=0;i<ans.size();++i)
    {
        printf("%d = %d\n",i,ans[i]);
    }
    return 0;
}