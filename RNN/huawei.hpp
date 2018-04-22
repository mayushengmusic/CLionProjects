//
// Created by Jaken on 2018/4/13.
//

#ifndef RNN_HUAWEI_HPP
#define RNN_HUAWEI_HPP
#include "lstm.hpp"
#include <limits>
#include <algorithm>

typedef std::vector<std::vector<int>> imat;


void maketrainningdata(mat &data,std::vector<mat> &input,std::vector<mat> &label){
    input.clear();label.clear();

    if(data.size()<=TIME_STEP)
        return;

    for(int i=0;i<=data.size()-TIME_STEP;++i)
    {
        mat inputele,labelele;
        for(int k=i;k<i+TIME_STEP;++k)
        {

            vec tem(data[k].size());

            for(int m=0;m<data[k].size();++m)
                tem[m]=data[k][m];

            if(i==0)
            {
                inputele.push_back(tem);
            }

            if(i==(data.size()-TIME_STEP))
            {
                labelele.push_back(tem);
            }

            if(i!=(data.size()-TIME_STEP)&&i!=0)
            {
                inputele.push_back(tem);
                labelele.push_back(tem);
            }

        }

        if(!inputele.empty())
            input.push_back(std::move(inputele));
        if(!labelele.empty())
            label.push_back(std::move(labelele));

    }

}


double normalization(int x,int Max,int Min){

    return 2.0*double(x-Min)/(double(Max-Min+ESPSILON))-1.0;
}

int unnormalization(double x,int Max,int Min){

    return int((x+1.0)*double(Max-Min+ESPSILON)/2.0+double(Min)+0.5);
}




std::vector<int> forecast(imat &data,int interval,int days){

    if(data.empty())
        return std::vector<int>();


   std::vector<int> max_(data[0].size(),std::numeric_limits<int>::min());
   std::vector<int> min_(data[0].size(),std::numeric_limits<int>::max());




   for(int j=0;j<data.size();++j)
   {

       for(int i=0;i<data[j].size();++i)
       {
           if(data[j][i]>max_[i])
                max_[i] = data[j][i];
           if(data[j][i]<min_[i])
                min_[i] = data[j][i];
       }
   }




   mat normal_data;

   normal_data.resize(data.size(),vec(data[0].size(),double(0.0)));

   for(int j=0;j<data.size();++j)
   {
       for(int i=0;i<data[j].size();++i)
       {
            normal_data[j][i]=normalization(data[j][i],max_[i],min_[i]);
       }
   }



    std::vector<arr> inputs,labels;

    maketrainningdata(normal_data,inputs,labels);



    rnn lstm(data[0].size(),data[0].size(),TIME_STEP);

    for(int i=0;i<INTER*inputs.size();++i)
    {
        static std::random_device gen;
        unsigned key = gen();
        lstm.backforward(inputs[key%inputs.size()],labels[key%labels.size()]);
        //show(inputs[key%inputs.size()]);
        //show(labels[key%labels.size()]);
        if(i%(inputs.size()*EPOLL)==0)
            LEARNNINGRATE=LEARNNINGRATE*DESC;

    }

    arr in=inputs.back();
    arr out;
    std::vector<int> ans(data[0].size(),0);

    for(int k=0;k<days+interval;++k)
    {

        lstm.forward(in,out);


        if(k>=interval)
        for(int i=0;i<ans.size();++i) {

            ans[i] +=unnormalization(out.back()[i],max_[i],min_[i]);

        }


        std::reverse(in.begin(),in.end());
        in.pop_back();
        std::reverse(in.begin(),in.end());
        in.push_back(out.back());
    }





    return ans;
}



#endif //RNN_HUAWEI_HPP
