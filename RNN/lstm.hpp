//
// Created by Jaken on 2018/4/12.
//

#ifndef RNN_LSTM_NEW_HPP
#define RNN_LSTM_NEW_HPP

#include <iostream>
#include <random>
#include "GlobalMacro.hpp"

typedef std::vector<std::vector<double>> mat;
typedef std::vector<std::vector<double>> arr;
typedef std::vector<double> vec;


void show(mat x);

static double myrand() {
    static std::random_device gen;
    unsigned rad = gen();

    if (rad % 2 == 1)
        return -(double(rad) - std::numeric_limits<unsigned>::min()) / double(std::numeric_limits<unsigned>::max());
    else
        return (double(rad) - std::numeric_limits<unsigned>::min()) / double(std::numeric_limits<unsigned>::max());
}

void initmat(mat &a) {

    for (int j = 0; j < a.size(); ++j)
        for (int i = 0; i < a[j].size(); ++i)
            a[j][i] = myrand() * 0.0001;

}

void initvec(vec &v) {
    for (int i = 0; i < v.size(); ++i)
        v[i] = myrand() * 0.0001;

}

static double sigmoid(double x) {
    return double(1.0) / (double(1.0) + exp(-x));
}

double d_sigmoid(double x) {
    return x * (double(1.0) - x);
}

double d_tanh(double x) {
    x = tanh(x);
    return double(1.0) - x * x;
}

void show(mat x) {

    if (x.empty()) {
        std::cout << "\n";
        std::cout << "EMPTY" << std::endl;
        return;
    }


    for (int j = 0; j < x.size(); ++j) {
        for (int i = 0; i < x[j].size(); ++i) {
            std::cout << x[j][i] << " \t";
        }
        std::cout << "\n";
    }
    std::cout << "________\n\n\n";
}

void show(vec x) {

    if (x.empty()) {
        std::cout << "\n";
        std::cout << "EMPTY" << std::endl;
        return;
    }


    for (int j = 0; j < x.size(); ++j) {

        std::cout << x[j] << " \t";

    }
    std::cout << "\n________\n\n\n";
}


mat mattanh(mat x) {
    for (int j = 0; j < x.size(); ++j)
        for (int i = 0; i < x[j].size(); ++i)
            x[j][i] = tanh(x[j][i]);

    return x;
}

vec vectanh(vec x) {

    for (int i = 0; i < x.size(); ++i)
        x[i] = tanh(x[i]);
    return x;

}

mat matsigmoid(mat x) {


    for (int j = 0; j < x.size(); ++j)
        for (int i = 0; i < x[j].size(); ++i)
            x[j][i] = sigmoid(x[j][i]);

    return x;
}

vec vecsigmoid(vec x) {

    for (int i = 0; i < x.size(); ++i)
        x[i] = sigmoid(x[i]);
    return x;

}

mat mathadamard(mat a, mat b) {

    if (a.empty() || b.empty())
        return mat();

    if (a.size() != b.size() || a[0].size() != b[0].size())
        return mat();

    for (int j = 0; j < a.size(); ++j)
        for (int i = 0; i < a[j].size(); ++i)
            a[j][i] = a[j][i] * b[j][i];

    return a;
}

vec vechadamard(vec a, vec b) {

    if (a.empty() || b.empty())
        return vec();

    if (a.size() != b.size())
        return vec();

    for (int i = 0; i < a.size(); ++i)
        a[i] = a[i] * b[i];

    return a;
}

mat operator+(mat a, mat b) {

    if (a.empty() || b.empty())
        return mat();

    if (a.size() != b.size() || a[0].size() != b[0].size())
        return mat();

    for (int j = 0; j < a.size(); ++j)
        for (int i = 0; i < a[j].size(); ++i)
            a[j][i] = a[j][i] + b[j][i];

    return a;
}

mat operator+(mat a, double b) {

    if (a.empty())
        return mat();


    for (int j = 0; j < a.size(); ++j)
        for (int i = 0; i < a[j].size(); ++i)
            a[j][i] = a[j][i] + b;

    return a;
}

mat operator-(mat a, mat b) {

    if (a.empty() || b.empty())
        return mat();

    if (a.size() != b.size() || a[0].size() != b[0].size())
        return mat();

    for (int j = 0; j < a.size(); ++j)
        for (int i = 0; i < a[j].size(); ++i)
            a[j][i] = a[j][i] - b[j][i];

    return a;
}

mat transport(mat a) {

    if (a.empty())
        return mat();

    mat b(a[0].size(), vec(a.size(), 0.0));

    for (int j = 0; j < a.size(); ++j) {
        for (int i = 0; i < a[j].size(); ++i) {
            b[i][j] = a[j][i];
        }
    }

    return b;
}

mat kroncker(mat a, mat b) {
    if (a.empty() || b.empty())
        return mat();

    mat res(a.size() * b.size(), vec(a[0].size() * b[0].size(), 0.0));
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < a[i].size(); ++j)
            for (int m = 0; m < b.size(); ++m)
                for (int n = 0; n < b[m].size(); ++n)
                    res[i * b.size() + m][j * b[m].size() + n] = a[i][j] * b[m][n];

    return res;

}

mat kroncker(mat a, vec b) {
    if (a.empty() || b.empty())
        return mat();

    mat res(a.size() * b.size(), vec(a[0].size(), 0.0));
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < a[i].size(); ++j)
            for (int m = 0; m < b.size(); ++m)
                res[i * b.size() + m][j] = a[i][j] * b[m];

    return res;
}

mat kroncker(vec a, vec b) {
    if (a.empty() || b.empty())
        return mat();

    mat res(a.size(), vec(b.size(), 0.0));

    for (int j = 0; j < res.size(); ++j)
        for (int i = 0; i < res[j].size(); ++i)
            res[j][i] = a[j] * b[i];

    return res;

}

mat operator*(double a, mat b) {
    for (int j = 0; j < b.size(); ++j)
        for (int i = 0; i < b[j].size(); ++i)
            b[j][i] = a * b[j][i];

    return b;
}

vec operator*(double a, vec b) {
    for (int j = 0; j < b.size(); ++j)
        b[j] = a * b[j];

    return b;
}

mat operator*(mat a, mat b) {
    if (a.empty() || b.empty())
        return mat();

    if (a[0].size() != b.size())
        return mat();

    mat c(a.size(), vec(b[0].size(), 0.0));
    for (int j = 0; j < c.size(); ++j)
        for (int i = 0; i < c[j].size(); ++i) {
            for (int k = 0; k < b.size(); ++k)
                c[j][i] += a[j][k] * b[k][i];
        }

    return c;
}

vec operator*(mat a, vec b) {
    if (a.empty() || b.empty())
        return vec();

    if (a[0].size() != b.size())
        return vec();

    vec c(a.size(), 0.0);

    for (int j = 0; j < a.size(); ++j) {
        for (int i = 0; i < a[j].size(); ++i)
            c[j] += a[j][i] * b[i];
    }
    return c;
}

mat square(mat x) {
    for (int j = 0; j < x.size(); ++j)
        for (int i = 0; i < x[j].size(); ++i)
            x[j][i] = x[j][i] * x[j][i];

    return x;
}

vec square(vec x) {
    for (int j = 0; j < x.size(); ++j)
        x[j] = x[j] * x[j];

    return x;
}

mat evolution(mat x) {
    for (int j = 0; j < x.size(); ++j)
        for (int i = 0; i < x[j].size(); ++i)
            x[j][i] = pow(x[j][i], 0.5);
    return x;
}

vec evolution(vec x) {
    for (int j = 0; j < x.size(); ++j)
        x[j] = pow(x[j], 0.5);
    return x;
}

mat reciprocal(mat x) {
    for (int j = 0; j < x.size(); ++j)
        for (int i = 0; i < x[j].size(); ++i)
            x[j][i] = double(1.0) / x[j][i];

    return x;
}

vec reciprocal(vec x) {
    for (int j = 0; j < x.size(); ++j)
        x[j] = double(1.0) / x[j];

    return x;
}

mat matonecutsquare(mat x) {
    for (int j = 0; j < x.size(); ++j)
        for (int i = 0; i < x[j].size(); ++i)
            x[j][i] = 1.0 - x[j][i] * x[j][i];
    return x;
}

vec veconecutsquare(vec x) {
    for (int j = 0; j < x.size(); ++j)
        x[j] = 1.0 - x[j] * x[j];
    return x;
}

mat matonecut(mat x) {
    for (int j = 0; j < x.size(); ++j)
        for (int i = 0; i < x[j].size(); ++i)
            x[j][i] = 1.0 - x[j][i];
    return x;
}

vec veconecut(vec x) {
    for (int j = 0; j < x.size(); ++j)
        x[j] = 1.0 - x[j];
    return x;
}

vec operator+(vec a, vec b) {
    if (a.size() != b.size())
        return vec();

    if (a.empty() || b.empty())
        return vec();

    for (int i = 0; i < a.size(); ++i)
        a[i] += b[i];
    return a;
}

vec operator+(vec a, double b) {
    if (a.empty())
        return vec();

    for (int i = 0; i < a.size(); ++i)
        a[i] += b;
    return a;
}

vec operator-(vec a, vec b) {
    if (a.size() != b.size())
        return vec();

    if (a.empty() || b.empty())
        return vec();

    for (int i = 0; i < a.size(); ++i)
        a[i] -= b[i];
    return a;
}


class adam {
public:
    adam(size_t outputdim, size_t inputdim) :
            wamt(outputdim, vec(inputdim, 0.0)), uamt(outputdim, vec(outputdim, 0.0)), bamt(outputdim, 1.0),
            wimt(outputdim, vec(inputdim, 0.0)), uimt(outputdim, vec(outputdim, 0.0)), bimt(outputdim, 1.0),
            wfmt(outputdim, vec(inputdim, 0.0)), ufmt(outputdim, vec(outputdim, 0.0)), bfmt(outputdim, 1.0),
            womt(outputdim, vec(inputdim, 0.0)), uomt(outputdim, vec(outputdim, 0.0)), bomt(outputdim, 1.0),
            wavt(outputdim, vec(inputdim, 0.0)), uavt(outputdim, vec(outputdim, 0.0)), bavt(outputdim, 1.0),
            wivt(outputdim, vec(inputdim, 0.0)), uivt(outputdim, vec(outputdim, 0.0)), bivt(outputdim, 1.0),
            wfvt(outputdim, vec(inputdim, 0.0)), ufvt(outputdim, vec(outputdim, 0.0)), bfvt(outputdim, 1.0),
            wovt(outputdim, vec(inputdim, 0.0)), uovt(outputdim, vec(outputdim, 0.0)), bovt(outputdim, 1.0) {

    }

    mat getadamdelta_wa(const mat &delta_wa) {


        wamt = BETA_1 * wamt + (1 - BETA_1) * delta_wa;
        wavt = BETA_2 * wavt + (1 - BETA_2) * square(delta_wa);

        mat wamt_ = (1.0 / (1 - BETA_1)) * wamt;
        mat wavt_ = (1.0 / (1 - BETA_2)) * wavt;

        return mathadamard(wamt_, (reciprocal(evolution(wavt_) + ESPSILON)));

    }

    mat getadamdelta_ua(const mat &delta_ua) {

        uamt = BETA_1 * uamt + (1 - BETA_1) * delta_ua;
        uavt = BETA_2 * uavt + (1 - BETA_2) * square(delta_ua);

        mat uamt_ = (1.0 / (1 - BETA_1)) * uamt;
        mat uavt_ = (1.0 / (1 - BETA_2)) * uavt;

        return mathadamard(uamt_, (reciprocal(evolution(uavt_) + ESPSILON)));

    }

    mat getadamdelta_wi(const mat &delta_wi) {

        wimt = BETA_1 * wimt + (1 - BETA_1) * delta_wi;
        wivt = BETA_2 * wivt + (1 - BETA_2) * square(delta_wi);

        mat wimt_ = (1.0 / (1 - BETA_1)) * wimt;
        mat wivt_ = (1.0 / (1 - BETA_2)) * wivt;

        return mathadamard(wimt_, (reciprocal(evolution(wivt_) + ESPSILON)));

    }

    mat getadamdelta_ui(const mat &delta_ui) {

        uimt = BETA_1 * uimt + (1 - BETA_1) * delta_ui;
        uivt = BETA_2 * uivt + (1 - BETA_2) * square(delta_ui);

        mat uimt_ = (1.0 / (1 - BETA_1)) * uimt;
        mat uivt_ = (1.0 / (1 - BETA_2)) * uivt;

        return mathadamard(uimt_, (reciprocal(evolution(uivt_) + ESPSILON)));

    }

    mat getadamdelta_wf(const mat &delta_wf) {

        wfmt = BETA_1 * wfmt + (1 - BETA_1) * delta_wf;
        wfvt = BETA_2 * wfvt + (1 - BETA_2) * square(delta_wf);

        mat wfmt_ = (1.0 / (1 - BETA_1)) * wfmt;
        mat wfvt_ = (1.0 / (1 - BETA_2)) * wfvt;

        return mathadamard(wfmt_, (reciprocal(evolution(wfvt_) + ESPSILON)));

    }

    mat getadamdelta_uf(const mat &delta_uf) {

        ufmt = BETA_1 * ufmt + (1 - BETA_1) * delta_uf;
        ufvt = BETA_2 * ufvt + (1 - BETA_2) * square(delta_uf);

        mat ufmt_ = (1.0 / (1 - BETA_1)) * ufmt;
        mat ufvt_ = (1.0 / (1 - BETA_2)) * ufvt;

        return mathadamard(ufmt_, (reciprocal(evolution(ufvt_) + ESPSILON)));

    }

    mat getadamdelta_wo(const mat &delta_wo) {

        womt = BETA_1 * womt + (1 - BETA_1) * delta_wo;
        wovt = BETA_2 * wovt + (1 - BETA_2) * square(delta_wo);

        mat womt_ = (1.0 / (1 - BETA_1)) * womt;
        mat wovt_ = (1.0 / (1 - BETA_2)) * wovt;

        return mathadamard(womt_, (reciprocal(evolution(wovt_) + ESPSILON)));

    }


    mat getadamdelta_uo(const mat &delta_uo) {

        uomt = BETA_1 * uomt + (1 - BETA_1) * delta_uo;
        uovt = BETA_2 * uovt + (1 - BETA_2) * square(delta_uo);

        mat uomt_ = (1.0 / (1 - BETA_1)) * uomt;
        mat uovt_ = (1.0 / (1 - BETA_2)) * uovt;

        return mathadamard(uomt_, (reciprocal(evolution(uovt_) + ESPSILON)));

    }

    vec getadamdelta_ba(const vec &delta_ba) {

        bamt = BETA_1 * bamt + (1 - BETA_1) * delta_ba;
        bavt = BETA_2 * bavt + (1 - BETA_2) * square(delta_ba);

        vec bamt_ = (1.0 / (1 - BETA_1)) * bamt;
        vec bavt_ = (1.0 / (1 - BETA_2)) * bavt;

        return vechadamard(bamt_, (reciprocal(evolution(bavt_) + ESPSILON)));

    }

    vec getadamdelta_bi(const vec &delta_bi) {

        bimt = BETA_1 * bimt + (1 - BETA_1) * delta_bi;
        bivt = BETA_2 * bivt + (1 - BETA_2) * square(delta_bi);

        vec bimt_ = (1.0 / (1 - BETA_1)) * bimt;
        vec bivt_ = (1.0 / (1 - BETA_2)) * bivt;

        return vechadamard(bimt_, (reciprocal(evolution(bivt_) + ESPSILON)));

    }


    vec getadamdelta_bf(const vec &delta_bf) {

        bfmt = BETA_1 * bfmt + (1 - BETA_1) * delta_bf;
        bfvt = BETA_2 * bfvt + (1 - BETA_2) * square(delta_bf);

        vec bfmt_ = (1.0 / (1 - BETA_1)) * bfmt;
        vec bfvt_ = (1.0 / (1 - BETA_2)) * bfvt;

        return vechadamard(bfmt_, (reciprocal(evolution(bfvt_) + ESPSILON)));

    }

    vec getadamdelta_bo(const vec &delta_bo) {

        bomt = BETA_1 * bomt + (1 - BETA_1) * delta_bo;
        bovt = BETA_2 * bovt + (1 - BETA_2) * square(delta_bo);

        vec bomt_ = (1.0 / (1 - BETA_1)) * bomt;
        vec bovt_ = (1.0 / (1 - BETA_2)) * bovt;

        return vechadamard(bomt_, (reciprocal(evolution(bovt_) + ESPSILON)));

    }


private:


    mat wamt, uamt;
    vec bamt;
    mat wimt, uimt;
    vec bimt;
    mat wfmt, ufmt;
    vec bfmt;
    mat womt, uomt;
    vec bomt;

    mat wavt, uavt;
    vec bavt;
    mat wivt, uivt;
    vec bivt;
    mat wfvt, ufvt;
    vec bfvt;
    mat wovt, uovt;
    vec bovt;


};


class rnn {
public:

    rnn(size_t outputdim, size_t inputdim, size_t timesteps) :
            wa(outputdim, vec(inputdim, 0.0)), ua(outputdim, vec(outputdim, 0.0)), ba(outputdim, 1.0),
            wi(outputdim, vec(inputdim, 0.0)), ui(outputdim, vec(outputdim, 0.0)), bi(outputdim, 1.0),
            wf(outputdim, vec(inputdim, 0.0)), uf(outputdim, vec(outputdim, 0.0)), bf(outputdim, 1.0),
            wo(outputdim, vec(inputdim, 0.0)), uo(outputdim, vec(outputdim, 0.0)), bo(outputdim, 1.0),
            outputdim(outputdim), inputdim(inputdim), timesteps(timesteps) {
        initmat(wa);
        initmat(ua);//initvec(ba);
        initmat(wi);
        initmat(ui);//initvec(bi);
        initmat(wf);
        initmat(uf);//initvec(bf);
        initmat(wo);
        initmat(uo);//initvec(bo);

    }

    void forward(arr &input, arr &outcopy) {
        out.clear();
        a_.clear();
        i_.clear();
        f_.clear();
        o_.clear();

        if (input.size() != timesteps)
            return;
        if (input.empty())
            return;
        for (int i = 0; i < input.size(); ++i)
            if (input[i].size() != inputdim) return;

        vec pre_out, pre_state;
        for (int i = 0; i < timesteps; ++i) {
            if (i == 0)
                pre_out = vec(outputdim, 0.0);

            vec at = vectanh(wa * input[i] + ua * pre_out + ba);

            vec it = vecsigmoid(wi * input[i] + ui * pre_out + bi);

            vec ft = vecsigmoid(wf * input[i] + uf * pre_out + bf);

            vec ot = vecsigmoid(wo * input[i] + uo * pre_out + bo);

            a_.push_back(at);
            i_.push_back(it);
            f_.push_back(ft);
            o_.push_back(ot);

            if (i == 0)
                pre_state = vec(outputdim, 0.0);
            vec statet = vechadamard(at, it) + vechadamard(ft, pre_state);
            state_.push_back(statet);
            pre_state = statet;
            vec outt = vechadamard(vectanh(statet), ot);
            pre_out = outt;
            out.push_back(outt);
        }
        outcopy = out;
    }


    void backforward(arr &input, arr &label) {
        if (input.empty() || label.empty())
            return;
        if (input.size() != timesteps || label.size() != timesteps)
            return;

        forward(input, out);
        delta_a.clear();
        delta_f.clear();
        delta_i.clear();
        delta_o.clear();
        delta_state.clear();
        delta_a.resize(timesteps);
        delta_f.resize(timesteps);
        delta_i.resize(timesteps);
        delta_o.resize(timesteps);
        delta_state.resize(timesteps);


        double loss(0.0);
        for (int j = 0; j < out.size(); ++j)
            for (int i = 0; i < out[j].size(); ++i)
                loss += (out[j][i] - label[j][i]) * (out[j][i] - label[j][i]) / 2.0;
        std::cout << "LOSS: " << loss << std::endl;


        vec dvalueoutt(outputdim, 0.0);
        for (int i = timesteps - 1; i >= 0; --i) {
            vec dvaluet;
            dvaluet = out[i] - label[i];

            //show(dvaluet);
            vec delta_outt = dvaluet + dvalueoutt;

            vec delta_statet = vechadamard(delta_outt, vechadamard(o_[i], veconecutsquare(vectanh(state_[i]))));

            if (i != timesteps - 1)
                delta_statet = delta_statet + vechadamard(delta_state[i + 1], f_[i + 1]);
            delta_state[i] = delta_statet;
            vec delta_at = vechadamard(vechadamard(delta_statet, i_[i]), veconecutsquare(a_[i]));

            vec delta_it = vechadamard(vechadamard(delta_statet, a_[i]), vechadamard(i_[i], veconecut(i_[i])));

            vec delta_ft = vec(outputdim, 0.0);
            if (i != 0)
                delta_ft = vechadamard(vechadamard(delta_statet, state_[i - 1]), vechadamard(f_[i], veconecut(f_[i])));

            vec delta_ot = vechadamard(vechadamard(delta_outt, vectanh(state_[i])),
                                       vechadamard(o_[i], veconecut(o_[i])));

            // vec delta_xt = transport(wa)*delta_at+transport(wi)*delta_it+transport(wf)*delta_ft+transport(wo)*delta_ot;
            dvalueoutt = transport(ua) * delta_at + transport(ui) * delta_it + transport(uf) * delta_ft +
                         transport(uo) * delta_ot;

            delta_a[i] = delta_at;
            delta_i[i] = delta_it;
            delta_f[i] = delta_ft;
            delta_o[i] = delta_ot;
        }

        mat delta_wa(outputdim, vec(inputdim, 0.0));
        mat delta_wi(outputdim, vec(inputdim, 0.0));
        mat delta_wf(outputdim, vec(inputdim, 0.0));
        mat delta_wo(outputdim, vec(inputdim, 0.0));


        for (int i = 0; i < timesteps; ++i) {
            delta_wa = delta_wa + kroncker(delta_a[i], input[i]);
            delta_wi = delta_wi + kroncker(delta_i[i], input[i]);
            delta_wf = delta_wf + kroncker(delta_f[i], input[i]);
            delta_wo = delta_wo + kroncker(delta_o[i], input[i]);
        }

        //show(delta_wa),show(delta_wi),show(delta_wf),show(delta_wo);

        mat delta_ua(outputdim, vec(outputdim, 0.0));
        mat delta_ui(outputdim, vec(outputdim, 0.0));
        mat delta_uf(outputdim, vec(outputdim, 0.0));
        mat delta_uo(outputdim, vec(outputdim, 0.0));


        for (int i = 0; i < timesteps - 1; ++i) {
            delta_ua = delta_ua + kroncker(delta_a[i + 1], out[i]);
            delta_ui = delta_ui + kroncker(delta_i[i + 1], out[i]);
            delta_uf = delta_uf + kroncker(delta_f[i + 1], out[i]);
            delta_uo = delta_uo + kroncker(delta_o[i + 1], out[i]);
        }

        //show(delta_ua),show(delta_ui),show(delta_uf),show(delta_uo);

        vec delta_ba(outputdim, 0.0);
        vec delta_bi(outputdim, 0.0);
        vec delta_bf(outputdim, 0.0);
        vec delta_bo(outputdim, 0.0);

        for (int i = 0; i < timesteps; ++i) {
            delta_ba = delta_ba + delta_a[i];
            delta_bi = delta_bi + delta_i[i];
            delta_bf = delta_bf + delta_f[i];
            delta_bo = delta_bo + delta_o[i];
        }

        //show(delta_ba),show(delta_bi),show(delta_bf),show(delta_bo);


        /* BASE SDG VERSION
        wa=wa-LEARNNINGRATE*delta_wa;
        wi=wi-LEARNNINGRATE*delta_wi;
        wf=wf-LEARNNINGRATE*delta_wf;
        wo=wo-LEARNNINGRATE*delta_wo;




        ua=ua-LEARNNINGRATE*delta_ua;
        ui=ui-LEARNNINGRATE*delta_ui;
        uf=uf-LEARNNINGRATE*delta_uf;
        uo=uo-LEARNNINGRATE*delta_uo;


        ba = ba -LEARNNINGRATE*delta_ba;
        bi = bi -LEARNNINGRATE*delta_bi;
        bf = bf -LEARNNINGRATE*delta_bf;
        bo = bo -LEARNNINGRATE*delta_bo;
        */

        //SDG WITH ADAM

        static adam adammachine(outputdim, inputdim);

        wa = wa - LEARNNINGRATE * adammachine.getadamdelta_wa(delta_wa);
        wi = wi - LEARNNINGRATE * adammachine.getadamdelta_wi(delta_wi);
        wf = wf - LEARNNINGRATE * adammachine.getadamdelta_wf(delta_wf);
        wo = wo - LEARNNINGRATE * adammachine.getadamdelta_wo(delta_wo);


        ua = ua - LEARNNINGRATE * adammachine.getadamdelta_ua(delta_ua);
        ui = ui - LEARNNINGRATE * adammachine.getadamdelta_ui(delta_ui);
        uf = uf - LEARNNINGRATE * adammachine.getadamdelta_uf(delta_uf);
        uo = uo - LEARNNINGRATE * adammachine.getadamdelta_uo(delta_uo);


        ba = ba - LEARNNINGRATE * adammachine.getadamdelta_ba(delta_ba);
        bi = bi - LEARNNINGRATE * adammachine.getadamdelta_bi(delta_bi);
        bf = bf - LEARNNINGRATE * adammachine.getadamdelta_bf(delta_bf);
        bo = bo - LEARNNINGRATE * adammachine.getadamdelta_bo(delta_bo);

    }


private:

    size_t outputdim, inputdim, timesteps;

    mat wa, ua;
    vec ba;
    mat wi, ui;
    vec bi;
    mat wf, uf;
    vec bf;
    mat wo, uo;
    vec bo;

    arr out;
    arr a_;
    arr i_;
    arr f_;
    arr o_;
    arr state_;

    arr delta_a;
    arr delta_i;
    arr delta_f;
    arr delta_o;
    arr delta_state;


};


#endif //RNN_LSTM_NEW_HPP
