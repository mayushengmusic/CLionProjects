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
typedef std::vector<std::vector<int>> imat;
typedef std::vector<int> ivec;

void show(mat x);

static double myrand() {

    static std::random_device gen;
    static std::mt19937 mt(gen());
    static std::uniform_real_distribution<double> uniform(-1e-4, 1e-4);
    return uniform(mt);

}

inline void initmat(mat &a) {

    for (int j = 0; j < a.size(); ++j)
        for (int i = 0; i < a[j].size(); ++i)
            a[j][i] = myrand();

}


inline double sigmoid(double x) {
    return double(1.0) / (double(1.0) + exp(-x));
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

void show(imat x) {

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


inline vec vectanh(vec x) {

    for (int i = 0; i < x.size(); ++i)
        x[i] = tanh(x[i]);
    return x;

}


inline vec vecsigmoid(vec x) {

    for (int i = 0; i < x.size(); ++i)
        x[i] = sigmoid(x[i]);
    return x;

}


inline mat mathadamard(mat a, mat b) {

    if (a.empty() || b.empty())
        return mat();

    if (a.size() != b.size() || a[0].size() != b[0].size())
        return mat();

    for (int j = 0; j < a.size(); ++j)
        for (int i = 0; i < a[j].size(); ++i)
            a[j][i] = a[j][i] * b[j][i];

    return a;
}

inline vec vechadamard(vec a, vec b) {

    if (a.empty() || b.empty())
        return vec();

    if (a.size() != b.size())
        return vec();

    for (int i = 0; i < a.size(); ++i)
        a[i] = a[i] * b[i];

    return a;
}

inline mat operator+(mat a, mat b) {

    if (a.empty() || b.empty())
        return mat();

    if (a.size() != b.size() || a[0].size() != b[0].size())
        return mat();

    for (int j = 0; j < a.size(); ++j)
        for (int i = 0; i < a[j].size(); ++i)
            a[j][i] = a[j][i] + b[j][i];

    return a;
}


inline mat operator+(mat a, double b) {

    if (a.empty())
        return mat();


    for (int j = 0; j < a.size(); ++j)
        for (int i = 0; i < a[j].size(); ++i)
            a[j][i] = a[j][i] + b;

    return a;
}

inline mat operator-(mat a, mat b) {

    if (a.empty() || b.empty())
        return mat();

    if (a.size() != b.size() || a[0].size() != b[0].size())
        return mat();

    for (int j = 0; j < a.size(); ++j)
        for (int i = 0; i < a[j].size(); ++i)
            a[j][i] = a[j][i] - b[j][i];

    return a;
}

inline mat transport(mat a) {

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

inline mat operator*(double a, mat b) {
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


inline mat transport(vec a) {

    mat res(1, a);

    return res;
}

mat operator*(vec a, mat b) {

    if (b.size() != 1)
        return mat();

    mat a_(a.size(), vec(1, 0.0));
    for (int i = 0; i < a_.size(); ++i)
        a_[i][0] = a[i];

    return a_ * b;
}

inline mat square(mat x) {
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

inline vec operator+(vec a, vec b) {
    if (a.size() != b.size())
        return vec();

    if (a.empty() || b.empty())
        return vec();

    for (int i = 0; i < a.size(); ++i)
        a[i] += b[i];
    return a;
}


inline vec operator+(vec a, double b) {
    if (a.empty())
        return vec();

    for (int i = 0; i < a.size(); ++i)
        a[i] += b;
    return a;
}

inline vec operator-(vec a, vec b) {
    if (a.size() != b.size())
        return vec();

    if (a.empty() || b.empty())
        return vec();

    for (int i = 0; i < a.size(); ++i)
        a[i] -= b[i];
    return a;
}


class rnn {
public:

    rnn(size_t outputdim, size_t inputdim, size_t hiddendim, size_t timesteps) :
            outputdim(outputdim), inputdim(inputdim), hiddendim(hiddendim), timesteps(timesteps),
            wa(hiddendim, vec(inputdim, 0.0)), ua(hiddendim, vec(hiddendim, 0.0)), ba(hiddendim, 1.0),
            wi(hiddendim, vec(inputdim, 0.0)), ui(hiddendim, vec(hiddendim, 0.0)), bi(hiddendim, 1.0),
            wf(hiddendim, vec(inputdim, 0.0)), uf(hiddendim, vec(hiddendim, 0.0)), bf(hiddendim, 1.0),
            wo(hiddendim, vec(inputdim, 0.0)), uo(hiddendim, vec(hiddendim, 0.0)), bo(hiddendim, 1.0),
            wy(outputdim, vec(hiddendim, 0.0)) {
        initmat(wa);
        initmat(ua);//initvec(ba);
        initmat(wi);
        initmat(ui);//initvec(bi);
        initmat(wf);
        initmat(uf);//initvec(bf);
        initmat(wo);
        initmat(uo);//initvec(bo);
        initmat(wy);

    }

    ~rnn() {

    }

    void forward(arr &input, arr &ycopy) {
        y.clear();
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
                pre_out = vec(hiddendim, 0.0);

            vec at = vectanh(wa * input[i] + ua * pre_out + ba);


            vec it = vecsigmoid(wi * input[i] + ui * pre_out + bi);


            vec ft = vecsigmoid(wf * input[i] + uf * pre_out + bf);

            vec ot = vecsigmoid(wo * input[i] + uo * pre_out + bo);

            a_.push_back(at);
            i_.push_back(it);
            f_.push_back(ft);
            o_.push_back(ot);

            if (i == 0)
                pre_state = vec(hiddendim, 0.0);
            vec statet = vechadamard(at, it) + vechadamard(ft, pre_state);
            state_.push_back(statet);
            pre_state = statet;
            vec outt = vechadamard(vectanh(statet), ot);
            pre_out = outt;

            out.push_back(outt);
            y.push_back(vectanh(wy * outt));

        }

        if (&ycopy != &y)
            ycopy = y;


    }


    void backforward(arr &input, arr &label) {
        if (input.empty() || label.empty())
            return;
        if (input.size() != timesteps || label.size() != timesteps)
            return;

        forward(input, y);
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


        delta_wy.clear();

        delta_wy.resize(outputdim, vec(hiddendim, 0.0));


        double loss(0.0);

        for (int i = 0; i < y.back().size(); ++i)
            loss += (y.back()[i] - label.back()[i]) * (y.back()[i] - label.back()[i]) / 2.0;

        std::cout << pow(loss, 0.5) << std::endl;


        vec dvalueoutt(hiddendim, 0.0);

        for (int i = int(timesteps - 1); i >= 0; --i) {
            vec dvaluet(hiddendim, 0.0);
            if (i == int(timesteps - 1)) {
                vec mid = vechadamard(y[i] - label[i], veconecutsquare(y[i]));
                delta_wy = delta_wy + mid * transport(out[i]);

                dvaluet = transport(wy) * mid;//need update

                //show(dvaluet);

            }

            vec delta_outt = dvaluet + dvalueoutt;

            vec delta_statet = vechadamard(delta_outt, vechadamard(o_[i], veconecutsquare(vectanh(state_[i]))));

            if (i != timesteps - 1)
                delta_statet = delta_statet + vechadamard(delta_state[i + 1], f_[i + 1]);

            delta_state[i] = delta_statet;
            vec delta_at = vechadamard(vechadamard(delta_statet, i_[i]), veconecutsquare(a_[i]));


            vec delta_it = vechadamard(vechadamard(delta_statet, a_[i]), vechadamard(i_[i], veconecut(i_[i])));


            vec delta_ft = vec(hiddendim, 0.0);
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

        mat delta_wa(hiddendim, vec(inputdim, 0.0));
        mat delta_wi(hiddendim, vec(inputdim, 0.0));
        mat delta_wf(hiddendim, vec(inputdim, 0.0));
        mat delta_wo(hiddendim, vec(inputdim, 0.0));


        for (int i = 0; i < timesteps; ++i) {
            delta_wa = delta_wa + kroncker(delta_a[i], input[i]);
            delta_wi = delta_wi + kroncker(delta_i[i], input[i]);
            delta_wf = delta_wf + kroncker(delta_f[i], input[i]);
            delta_wo = delta_wo + kroncker(delta_o[i], input[i]);
        }

        //show(delta_wa),show(delta_wi),show(delta_wf),show(delta_wo);

        mat delta_ua(hiddendim, vec(hiddendim, 0.0));
        mat delta_ui(hiddendim, vec(hiddendim, 0.0));
        mat delta_uf(hiddendim, vec(hiddendim, 0.0));
        mat delta_uo(hiddendim, vec(hiddendim, 0.0));


        for (int i = 0; i < timesteps - 1; ++i) {
            delta_ua = delta_ua + kroncker(delta_a[i + 1], out[i]);
            delta_ui = delta_ui + kroncker(delta_i[i + 1], out[i]);
            delta_uf = delta_uf + kroncker(delta_f[i + 1], out[i]);
            delta_uo = delta_uo + kroncker(delta_o[i + 1], out[i]);
        }

        //show(delta_ua),show(delta_ui),show(delta_uf),show(delta_uo);

        vec delta_ba(hiddendim, 0.0);
        vec delta_bi(hiddendim, 0.0);
        vec delta_bf(hiddendim, 0.0);
        vec delta_bo(hiddendim, 0.0);

        for (int i = 0; i < timesteps; ++i) {
            delta_ba = delta_ba + delta_a[i];

            delta_bi = delta_bi + delta_i[i];

            delta_bf = delta_bf + delta_f[i];
            delta_bo = delta_bo + delta_o[i];

        }




        // BASE SDG VERSION

        static mat v_wa(hiddendim, vec(outputdim, 0.0));
        v_wa = BETA * v_wa + delta_wa;
        wa = wa - LEARNNINGRATE * v_wa;

        static mat v_wi(hiddendim, vec(outputdim, 0.0));
        v_wi = BETA * v_wi + delta_wi;
        wi = wi - LEARNNINGRATE * v_wi;

        static mat v_wf(hiddendim, vec(outputdim, 0.0));
        v_wf = BETA * v_wf + delta_wf;
        wf = wf - LEARNNINGRATE * v_wf;

        static mat v_wo(hiddendim, vec(outputdim, 0.0));
        v_wo = BETA * v_wo + delta_wo;
        wo = wo - LEARNNINGRATE * v_wo;

        static mat v_ua(hiddendim, vec(hiddendim, 0.0));
        v_ua = BETA * v_ua + delta_ua;
        ua = ua - LEARNNINGRATE * v_ua;

        static mat v_ui(hiddendim, vec(hiddendim, 0.0));
        v_ui = BETA * v_ui + delta_ui;
        ui = ui - LEARNNINGRATE * v_ui;

        static mat v_uf(hiddendim, vec(hiddendim, 0.0));
        v_uf = BETA * v_uf + delta_uf;
        uf = uf - LEARNNINGRATE * v_uf;

        static mat v_uo(hiddendim, vec(hiddendim, 0.0));
        v_uo = BETA * v_uo + delta_uo;
        uo = uo - LEARNNINGRATE * v_uo;

        static vec v_ba(hiddendim, 0.0);
        v_ba = BETA * v_ba + delta_ba;
        ba = ba - LEARNNINGRATE * v_ba;

        static vec v_bi(hiddendim, 0.0);
        v_bi = BETA * v_bi + delta_bi;
        bi = bi - LEARNNINGRATE * v_bi;

        static vec v_bf(hiddendim, 0.0);
        v_bf = BETA * v_bf + delta_bf;
        bf = bf - LEARNNINGRATE * v_bf;

        static vec v_bo(hiddendim, 0.0);
        v_bo = BETA * v_bo + delta_bo;
        bo = bo - LEARNNINGRATE * v_bo;

        static mat v_wy(outputdim, vec(hiddendim, 0.0));
        v_wy = BETA * v_wy + delta_wy;
        wy = wy - LEARNNINGRATE * v_wy;


    }


private:

    size_t outputdim, inputdim, hiddendim, timesteps;


    mat wa, ua;
    vec ba;
    mat wi, ui;
    vec bi;
    mat wf, uf;
    vec bf;
    mat wo, uo;
    vec bo;


    arr out;
    arr y;


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

    mat wy;


    mat delta_wy;


};


#endif //RNN_LSTM_NEW_HPP
