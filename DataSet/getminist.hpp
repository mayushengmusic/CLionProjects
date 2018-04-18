//
// Created by jaken on 3/8/17.
//
#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#ifndef DATASET_GETMINIST_HPP
#define DATASET_GETMINIST_HPP
uint32_t LittleEndianToBigEndian(uint32_t val)
{
    val=((val<<8)&0xFF00FF00)|((val>>8)&0xFF00FF);
    return (val<<16|val>>16);
}

void DrawImage(std::ifstream & bindata,uint32_t rows,uint32_t columns)
{
    cv::Mat image(cv::Size(rows,columns),CV_8UC1);
    for(uint32_t i=0;i<rows;i++)
    {
        uchar *data = image.ptr<uchar>(i);
        for(uint32_t j=0;j<columns;j++)
        {
            bindata.read(reinterpret_cast<char *>(data+j),sizeof(uchar));
        }
    }

    std::string savePath("/home/jaken/WorkSpace/MINST/TEST/minst_");
    static unsigned num=0;
    savePath+=std::to_string(num++);
    savePath+=std::string(".jpg");
    cv::imwrite(savePath.c_str(),image);
}

void MakeLabel(std::ifstream & bindata)
{
    static std::ofstream label("/home/jaken/WorkSpace/MINST/test_mnist_label.txt");
    static uchar temp;
    bindata.read(reinterpret_cast<char *>(&temp),sizeof(uchar));
    std::string savePath("WorkSpace/MINST/TEST/minst_");
    static unsigned num=0;
    savePath+=std::to_string(num++);
    savePath+=std::string(".jpg");
    static unsigned label_num;
    label_num= temp;
    label<<savePath<<" "<<label_num<<std::endl;
}

#endif //DATASET_GETMINIST_HPP
