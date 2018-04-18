//
// Created by jaken on 3/8/17.
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
#ifndef DATASET_STICK_HPP
#define DATASET_STICK_HPP
bool ReadFloader(const std::string &FloaderPath,std::vector<std::string> &IMGPath)
{

    DIR *MainPathDir = opendir(FloaderPath.c_str());
    if(MainPathDir==NULL)
    {
        std::cerr<<"cannot open the directory"<<std::endl;

        return false;
    }

    std::string currentPath;
    std::queue<std::string> PathQueue;
    PathQueue.push(FloaderPath);

    while(!PathQueue.empty())
    {
        currentPath=PathQueue.front();
        PathQueue.pop();


        DIR *currentPathDir=opendir(currentPath.c_str());
        if(currentPathDir==NULL)
            continue;

        struct dirent * leap = readdir(currentPathDir);
        while(leap)
        {
            std::regex jpg(".*\\.jpg$");
            std::string name(leap->d_name);

            if(std::regex_match(name,jpg))
            {
                std::string path = currentPath+std::string("/")+std::string(leap->d_name);

                IMGPath.push_back(path);

            }
            else
            {
                if(strcmp(leap->d_name,".")!=0 && strcmp(leap->d_name,"..")!=0)
                {
                    std::string path = currentPath+std::string("/")+std::string(leap->d_name);
                    PathQueue.push(path);
                }

            }


            leap = readdir(currentPathDir);

        }

    }

    return true;
}

void ResizeIMG(cv::Mat & image)
{
    cv::Size geometry(28,28);
    if(image.size()!=geometry)
        cv::resize(image,image,geometry);

}

void stickIMG(cv::Mat & image)
{
    cv::Mat regular(28,28,CV_8UC1,cv::Scalar(0));
    cv::Size geometry=image.size();
    if(geometry.height>geometry.width)
    {
        double multiple = 26.0/geometry.height;
        double new_width = geometry.width*multiple;


        cv::resize(image,image,cv::Size((int)new_width+1,26));
        cv::Mat imageROI(regular,cv::Rect((28-image.cols)/2,1,image.cols,image.rows));
        image.copyTo(imageROI);
        regular.copyTo(image);
    }
    else
    {
        double multiple = 26.0/geometry.width;
        double new_height = geometry.height*multiple;

            cv::resize(image, image, cv::Size(26, (int) new_height));
            cv::Mat imageROI(regular, cv::Rect(1, (28 - image.rows) / 2, image.cols, image.rows));
            image.copyTo(imageROI);
            regular.copyTo(image);

    }




}


#endif //DATASET_STICK_HPP
