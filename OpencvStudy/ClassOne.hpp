//
// Created by jaken on 16-10-3.
//

#ifndef OPENCVSTUDY_CLASSONE_HPP
#define OPENCVSTUDY_CLASSONE_HPP
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

void onMouse(int event, int x, int y, int flags, void * param){

    cv::Mat *im = reinterpret_cast<cv::Mat *>(param);
    switch (event){
        case CV_EVENT_LBUTTONDOWN:
            std::cout<<x<<" "<<y<<":"<< static_cast<int>(im->at<uchar>(cv::Point(x,y)))<<std::endl;
            break;
    }
}

void myhandle(cv::Mat &image)
{
    cv::namedWindow("image");
    cv::putText(image,"This is a beauty!",cv::Point(40,200),cv::FONT_HERSHEY_PLAIN,2.0,255,3);
    cv::circle(image,cv::Point(155,110),65,255,5);
    cv::setMouseCallback("image",onMouse, reinterpret_cast<void*>(&image));
    cv::imshow("image",image);
    cv::waitKey(0);
}
#endif //OPENCVSTUDY_CLASSONE_HPP
