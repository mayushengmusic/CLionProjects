//
// Created by jaken on 3/9/17.
//
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <queue>
#include <regex>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#ifndef DATASET_SPLITNUMBER_HPP
#define DATASET_SPLITNUMBER_HPP

void findEdge(const std::vector<cv::Point> &src,std::pair<int,int> &loc,std::pair<int,int> &area)
{
    int left=src[0].x,right=src[0].x;
    int top=src[0].y,down=src[0].y;

   for(auto & point:src)
   {
       if(point.x<left)
           left=point.x;
       if(point.x>right)
           right=point.x;
       if(point.y<top)
           top=point.y;
       if(point.y>down)
           down=point.y;

   }




    loc.first=left;
    loc.second=top;

    area.first=right-left;
    area.second=down-top;


}




void splitImage(cv::Mat & image,std::vector<cv::Mat> & splitIMG)
{

    cv::Mat binImage;
    cv::threshold(image,binImage,200,255,cv::THRESH_BINARY_INV| CV_THRESH_OTSU);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binImage,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    //cv::Mat result(image.size(),CV_8U,cv::Scalar(255));
    //cv::drawContours(result,contours,-1,0,1); 绘出连通域

    std::pair<int,int> loc;
    std::pair<int,int> area;
    std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> locwitharea;
    for(auto &x: contours)
    {
        findEdge(x,loc,area);
        if(area.first==0||area.second==0)
            continue;
        locwitharea.push_back(std::make_pair(loc,area));
    }

    std::sort(locwitharea.begin(),locwitharea.end(),[](std::pair<std::pair<int,int>,std::pair<int,int>> &a,std::pair<std::pair<int,int>,std::pair<int,int>> &b)
              {
                  return a.first.first<b.first.first;
              }
    );

    for(auto &x: locwitharea) {
        cv::Mat temp(image, cv::Rect(x.first.first, x.first.second, x.second.first, x.second.second));
        splitIMG.emplace_back(temp.clone());
    }

}
#endif //DATASET_SPLITNUMBER_HPP
