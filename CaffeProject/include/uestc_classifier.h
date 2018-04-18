//
// Created by jaken on 16-10-11.
//
#include <caffe/caffe.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#ifndef CAFFEPROJECT_UESTC_CLASSIFIER_H
#define CAFFEPROJECT_UESTC_CLASSIFIER_H

using std::string;
using namespace caffe;
namespace clf {
    class uestc_classifier {

    public:
        uestc_classifier(const string &model_file,
                         const string &trained_file, const cv::Scalar &means);

        std::vector<float> Predict(cv::Mat &img);

    private:

        void WrapInputLayer(std::vector<cv::Mat> *input_channels);

        void copyimegtoinput(const cv::Mat &img,
                             std::vector<cv::Mat> *input_channels);

        void prehandleimage(cv::Mat &img);

    private:
        std::shared_ptr<Net<float> > net_;
        cv::Size input_geometry_;
        int num_channels_;
        cv::Scalar means;
        std::vector<cv::Mat> input_channels;
    };

}
#endif //CAFFEPROJECT_UESTC_CLASSIFIER_H
