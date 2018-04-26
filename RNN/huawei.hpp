//
// Created by Jaken on 2018/4/13.
//

#ifndef RNN_HUAWEI_HPP
#define RNN_HUAWEI_HPP

#include "lstm.hpp"
#include "datapreprocess.hpp"
#include <limits>
#include <algorithm>


ivec forecast(imat &data, int interval, int days) {


    datapreprocess proc;

    std::vector<mat> input, label;

    proc(data, input, label);


    rnn lstm(data.back().size(), data.back().size(), HIDDENDIM, TIME_STEP);


    for (int i = 0; i < INTER; ++i) {

        for (int j = 0; j < input.size(); ++j) {
            lstm.backforward(input[j], label[j]);

        }

        if (i % EPOLL == 0)
            LEARNNINGRATE = LEARNNINGRATE * DESC;

    }


    mat in(input.back());
    mat ans;
    for(int i=0;i<days+interval;++i)
    {
        mat out;
        lstm.forward(in, out);

        if(i>=interval)
           ans.push_back(out.back());

    }


    proc.untrans(ans);


    ivec res(ans.back().size(), 0);

    for (int j = 0; j < ans.size(); ++j)
        for (int i = 0; i < ans[j].size(); ++i) {
            res[i] += int(ans[j][i]);
        }


    return res;

}


#endif //RNN_HUAWEI_HPP
