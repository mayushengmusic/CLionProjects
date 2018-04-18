//
// Created by jaken on 16-10-11.
//

#include "../include/uestc_classifier.h"

clf::uestc_classifier::uestc_classifier(const string &model_file, const string &trained_file,const cv::Scalar& means) {

#ifdef CPU_ONLY
    Caffe::set_mode(Caffe::CPU);
#else
    Caffe::SetDevice(0);
    Caffe::set_mode(Caffe::GPU);
#endif

    net_.reset(new Net<float>(model_file, TEST));
    net_->CopyTrainedLayersFrom(trained_file);
    CHECK_EQ(net_->num_inputs(), 1) << "Network should have exactly one input.";
    CHECK_EQ(net_->num_outputs(), 1) << "Network should have exactly one output.";
    num_channels_=net_->input_blobs()[0]->channels();
    CHECK(num_channels_ == 3 || num_channels_ == 1)
    << "Input layer should have 1 or 3 channels.";
    input_geometry_ = cv::Size(net_->input_blobs()[0]->width(), net_->input_blobs()[0]->height());
    this->means = means;

    Blob<float>* input_layer = net_->input_blobs()[0];
    input_layer->Reshape(1, num_channels_,
                         input_geometry_.height, input_geometry_.width);
    /* Forward dimension change to all layers. */
    net_->Reshape();

}

void clf::uestc_classifier::prehandleimage(cv::Mat &img) {

    if (img.channels() == 3 && num_channels_ == 1)
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    else if (img.channels() == 4 && num_channels_ == 1)
        cv::cvtColor(img, img, cv::COLOR_BGRA2GRAY);
    else if (img.channels() == 4 && num_channels_ == 3)
        cv::cvtColor(img, img, cv::COLOR_BGRA2BGR);
    else if (img.channels() == 1 && num_channels_ == 3)
        cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);

    if (img.size() != input_geometry_)
        cv::resize(img, img, input_geometry_);

    if (num_channels_ == 3)
        img.convertTo(img, CV_32FC3);
    else
        img.convertTo(img, CV_32FC1);

}

void clf::uestc_classifier::WrapInputLayer(std::vector<cv::Mat> *input_channels) {//Wrap inputlayer to cv::Mat

    Blob<float>* input_layer = net_->input_blobs()[0];
    int width = input_layer->width();
    int height = input_layer->height();
    float* input_data = input_layer->mutable_cpu_data();
    for (int i = 0; i < input_layer->channels(); ++i) {
        cv::Mat channel(height, width, CV_32FC1, input_data);
        input_channels->push_back(channel);
        input_data += width * height;
    }

}

void clf::uestc_classifier::copyimegtoinput(const cv::Mat &img, std::vector<cv::Mat> *input_channels) {//Copy img to inputlayer



    cv::subtract(img,means,img);//subtract means;
    cv::split(img,*input_channels);

    CHECK(reinterpret_cast<float*>(input_channels->at(0).data)
          == net_->input_blobs()[0]->cpu_data())
    << "Input channels are not wrapping the input layer of the network.";


}

std::vector<float> clf::uestc_classifier::Predict(cv::Mat &img) {//predict the results by the img

    WrapInputLayer(&input_channels);
    prehandleimage(img);
    copyimegtoinput(img, &input_channels);

    net_->ForwardPrefilled();
    Blob<float>* output_layer = net_->output_blobs()[0];
    const float* begin = output_layer->cpu_data();
    const float* end = begin + output_layer->count();
    return std::vector<float >(begin,end);
}