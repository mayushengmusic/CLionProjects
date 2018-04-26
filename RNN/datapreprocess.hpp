//
// Created by jaken on 18-4-24.
//

#ifndef RNN_DATAPREPROCESS_HPP
#define RNN_DATAPREPROCESS_HPP

#include "lstm.hpp"


class datapreprocess{

public:
    datapreprocess()= default;
    void operator()(imat &data,std::vector<mat> &input,std::vector<mat> &label);
    void untrans(mat &data){

        unnormalization(data);
        unstandardization(data);


    }


private:


    mat imattomat(imat &data);
    void findmaxandmin(mat &data);
    void findmeansandvars(mat &data);
    void normalization(mat &data);
    void unnormalization(mat &data);
    void unstandardization(mat &data);
    void standardization(mat &data);
    void maketrainningdata(mat &data, std::vector<mat> &input, std::vector<mat> &label);

    vec maxs,mins;
    vec means,vars;


};




void datapreprocess::operator()(imat &data, std::vector<mat> &input, std::vector<mat> &label) {


    auto data_m = imattomat(data);

    findmeansandvars(data_m);

   standardization(data_m);


    findmaxandmin(data_m);

    normalization(data_m);


    maketrainningdata(data_m,input,label);
}



mat datapreprocess::imattomat(imat &data) {

    mat res;

    res.resize(data.size(),vec(data.back().size(),double(0.0)));

    for(int j=0;j<res.size();++j)
    {
        for(int i=0;i<res[j].size();++i)
            res[j][i]=data[j][i];
    }

    return res;
}


void datapreprocess::findmaxandmin(mat &data) {

    maxs.resize(data.back().size(),std::numeric_limits<double>::min());
    mins.resize(data.back().size(),std::numeric_limits<double>::max());

    for(int j=0;j<data.size();++j)
        for(int i=0;i<data[j].size();++i)
        {
            if(maxs[i]<data[j][i])
                maxs[i]=data[j][i];
            if(mins[i]>data[j][i])
                mins[i]=data[j][i];
        }

}


void datapreprocess::findmeansandvars(mat &data) {
    means.resize(data.back().size(),0.0);
    vars.resize(data.back().size(),0.0);

    for(int j=0;j<data.size();++j)
        for(int i=0;i<data[j].size();++i)
        {
            means[i]+=data[j][i];
        }

    for(int i=0;i<means.size();++i)
        means[i]=means[i]/double(data.size());

    for(int j=0;j<data.size();++j)
        for(int i=0;i<data[j].size();++i)
        {
           vars[i]+=pow(data[j][i]-means[i],2);
        }

    for(int i=0;i<vars.size();++i)
        vars[i]=vars[i]/double(data.size());

}


void datapreprocess::normalization(mat &data) {

    for(int j=0;j<data.size();++j)
        for(int i=0;i<data[j].size();++i)
        {
            data[j][i]=(data[j][i]-mins[i])/((maxs[i]-mins[i]+1));
            //data[j][i]=data[j][i]*2.0-1.0;

        }
}

void datapreprocess::unnormalization(mat &data) {

    for(int j=0;j<data.size();++j)
        for(int i=0;i<data[j].size();++i)
        {
           // data[j][i]=(data[j][i]+1.0)/2.0;
            data[j][i]=data[j][i]*(maxs[i]-mins[i]+1)+mins[i];
        }
}

void datapreprocess::standardization(mat &data) {
    for(int j=0;j<data.size();++j)
        for(int i=0;i<data[j].size();++i)
        {
            data[j][i]=(data[j][i]-means[i])/((pow(vars[i],0.5)+1e-8));
        }
}

void datapreprocess::unstandardization(mat &data){
    for(int j=0;j<data.size();++j)
        for(int i=0;i<data[j].size();++i)
        {
            data[j][i]=floor(data[j][i]*(pow(vars[i],0.5))+means[i]+0.5);
        }
}



void datapreprocess::maketrainningdata(mat &data, std::vector<mat> &input, std::vector<mat> &label) {
    input.clear();
    label.clear();

    if (data.size() <= TIME_STEP)
        return;

    for (int i = 0; i <= data.size() - TIME_STEP; ++i) {
        mat inputele, labelele;
        for (int k = i; k < i + TIME_STEP; ++k) {

            vec tem(data[k].size());

            for (int m = 0; m < data[k].size(); ++m)
                tem[m] = data[k][m];

            if (i == 0) {
                inputele.push_back(tem);
            }

            if (i == (data.size() - TIME_STEP)) {
                labelele.push_back(tem);
            }

            if (i != (data.size() - TIME_STEP) && i != 0) {
                inputele.push_back(tem);
                labelele.push_back(tem);
            }

        }

        if (!inputele.empty())
            input.push_back(std::move(inputele));
        if (!labelele.empty())
            label.push_back(std::move(labelele));

    }

}




#endif //RNN_DATAPREPROCESS_HPP
