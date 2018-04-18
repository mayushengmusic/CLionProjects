#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
int main() {

    cv::Mat image = cv::imread("/home/jaken/Temp/h.jpg",CV_LOAD_IMAGE_COLOR);

    cv::Mat image2 = cv::imread("/home/jaken/Temp/logo.jpg",CV_LOAD_IMAGE_COLOR);
    cv::resize(image,image,cv::Size(512,512),0,0,CV_INTER_LINEAR);
   cv::Mat imageROI(image,cv::Rect(image.cols-image2.cols,image.rows-image2.rows,image2.cols,image2.rows));
   image2.copyTo(imageROI);
    cv::imshow("pic",image);
    cv::waitKey(0);
    return 0;

}