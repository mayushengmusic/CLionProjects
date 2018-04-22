#include "huawei.hpp"


int main() {


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


    return 0;

}