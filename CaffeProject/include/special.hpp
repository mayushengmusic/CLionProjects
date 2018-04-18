//
// Created by jaken on 16-12-10.
//
#include "uestc_classifier.h"
#include <fstream>
#include <boost/filesystem.hpp>
#include "json.hpp"
#include "server_http.hpp"

#ifndef WEBCPP_SPECIAL_HPP
#define WEBCPP_SPECIAL_HPP
using namespace std;

typedef SimpleWeb::Server HttpServer;
class SpecialHandle{
public:
    static function<void(std::shared_ptr<HttpServer::Response>,std::shared_ptr<HttpServer::Request>)> caffehandle(clf::uestc_classifier & classifier,std::string &basepath);
};


function<void(std::shared_ptr<HttpServer::Response>,std::shared_ptr<HttpServer::Request>)> SpecialHandle::caffehandle(clf::uestc_classifier & classifier,std::string &basepath) {


    auto Test = [&](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
    {
        string ImageName=request->path_match[1];
        std::string completepath=basepath+ImageName;
        stringstream content_stream;
        nlohmann::json jsontable;
        try {

            cv::Mat image = cv::imread(completepath.c_str(),CV_LOAD_IMAGE_COLOR);
            std::vector<float> ans = classifier.Predict(image);
            //you maybe need to modify this code
            //
            jsontable["sex"]=ans[0];
            jsontable["sexy"]=ans[1];
            jsontable["normal"]=ans[2];
            //
            time_t tt = time(NULL);
            tm* t= localtime(&tt);

            std::clog<<"date:"<<(t->tm_year+1900)<<"."<<(t->tm_mon+1)<<"."<<t->tm_mday<<"\t"<<t->tm_hour<<":"<<t->tm_min<<":" \
                     <<t->tm_sec<<"\t"<<completepath<<'\n';


        }catch (...)
        {

            jsontable["sex"]="null";
            jsontable["sexy"]="null";
            jsontable["normal"]="null";
            time_t tt = time(NULL);
            tm* t= localtime(&tt);

            std::clog<<"date:"<<(t->tm_year+1900)<<"."<<(t->tm_mon+1)<<"."<<t->tm_mday<<"\t"<<t->tm_hour<<":"<<t->tm_min<<":" \
                     <<t->tm_sec<<"\t"<<completepath<<'\n';

        }



        content_stream<<jsontable;
        content_stream.seekp(0,ios::end);
        *response << "HTTP/1.1 200 OK\r\nContent-Length: "<< content_stream.tellp() << "\r\n\r\n" << content_stream.rdbuf();
    };
    return Test;
}


#endif //WEBCPP_SPECIAL_HPP
