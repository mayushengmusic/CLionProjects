#include "../include/server_http.hpp"
#include "../include/special.hpp"
#include "../include/default.hpp"



int main(int argc,char **argv) {

    const string model="/home/jaken/google/deploy.prototxt";//modify this string for your model define file location
    const string trained = "/home/jaken/google/final.caffemodel";//modify this string for your trained file
    cv::Scalar means(104,117,123);
    clf::uestc_classifier classifier(model,trained,means);
    HttpServer server(8080, 1);//8080 represent the server port,1 represent the thread number
    std::string basepath("/tmp/exc/");//the path where your images with put in


    server.resource["^/caffe\\?key=(.*)$"]["GET"] = SpecialHandle::caffehandle(classifier,basepath);
    server.default_resource["GET"] = DefaultMethod();
    thread server_thread([&server](){
        server.start();
    });

    server_thread.join();

    return 0;


}
