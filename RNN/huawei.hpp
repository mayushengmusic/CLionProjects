//
// Created by Jaken on 2018/4/13.
//

#ifndef RNN_HUAWEI_HPP
#define RNN_HUAWEI_HPP
#include "lstm_god.hpp"
#include <limits>

typedef std::vector<std::vector<int>> imat;

double normalization(double x,double Mean,double Var,double Min,double Max){
   double h_x=(x-Mean)/Var;
   double h_max = (Max-Mean)/Var;
   double h_min = (Min-Mean)/Var;
   return h_x/(h_max-h_min);
}

double unnormalization(double x,double Mean,double Var,double Min,double Max){
    double h_max = (Max-Mean)/Var;
    double h_min = (Min-Mean)/Var;
    return x*(h_max-h_min)*Var+Mean+0.5;

}

void maketrainningdata(imat &data,std::vector<mat> &input,std::vector<mat> &label){
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


std::vector<int> forecast(imat &data,int days){

    if(data.empty())
        return std::vector<int>();


    double Mean = 0.0;
    double Var = 0.0;
    double MaxNum = std::numeric_limits<double>::min();
    double MinNum = std::numeric_limits<double>::max();

    for(auto &y: data)
        for(auto &x: y)
        {
                Mean+=double(x);

                if(MaxNum<double(x))
                    MaxNum=double(x);
                if(MinNum>double(x))
                    MinNum=double(x);

        }

    Mean = Mean/data.size();


    for(auto &y: data)
        for(auto &x: y)
        {
            Var += (double(x)-Mean)*(double(x)-Mean);
        }

    Var =Var/data.size();



    std::vector<arr> inputs,labels;

    maketrainningdata(data,inputs,labels);

    for(auto &x: labels)
        for(auto &y: x)
            for(auto &z: y)
                z=normalization(z,Mean,Var,MinNum,MaxNum);

    for(auto &x: inputs)
        for(auto &y: x)
            for(auto &z: y)
                z=normalization(z,Mean,Var,MinNum,MaxNum);

    rnn lstm(data[0].size(),data[0].size(),TIME_STEP);

    for(int i=0;i<INTER*inputs.size();++i)
    {
       static std::random_device gen;
        unsigned key = gen();
        lstm.backforward(inputs[key%inputs.size()],labels[key%labels.size()]);
        //show(inputs[key%inputs.size()]);show(labels[key%labels.size()]);///
    }

    arr in=inputs.back();
    arr out;
    std::vector<int> ans(data[0].size(),0);

    for(int k=0;k<days;++k)
    {
        //show(in);
        lstm.forward(in,out);
        for(int i=0;i<ans.size();++i) {
            //std::cout<<unnormalization(out.back()[i], MaxNum, MinNum)<<std::endl;
            ans[i] += unnormalization(out.back()[i], Mean, Var,MinNum,MaxNum);
        }
        //std::cout<<"--------"<<std::endl;
        std::reverse(in.begin(),in.end());
        in.pop_back();
        std::reverse(in.begin(),in.end());
        /**
        for(int i=0;i<out.back().size();++i)
            out.back()[i]=(double)unnormalization(out.back()[i],MaxNum,MinNum);
        **/
        in.push_back(out.back());
    }



    return ans;
}



#endif //RNN_HUAWEI_HPP
