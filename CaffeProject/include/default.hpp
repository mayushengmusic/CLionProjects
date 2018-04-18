//
// Created by jaken on 16-12-10.
//
#include "server_http.hpp"
#include <fstream>
#include <boost/filesystem.hpp>

#ifndef WEBCPP_DEFAULT_HPP
#define WEBCPP_DEFAULT_HPP
using namespace std;
typedef SimpleWeb::Server HttpServer;

//Default GET-example. If no other matches, this anonymous function will be called.
//Will respond with content in the web/-directory, and its subdirectories.
//Default file: index.html
//Can for instance be used to retrieve an HTML 5 client that uses REST-resources on this server



function<void(std::shared_ptr<HttpServer::Response>,std::shared_ptr<HttpServer::Request>)> DefaultMethod() {

    return [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {


            string content = "NOT SERVER FOR OTHER APPLICATION!";
            *response<<string("HTTP/1.1 400 Bad Request\r\nContent-Length: ")<<content.length() << "\r\n\r\n" << content;
    };
}

#endif //WEBCPP_DEFAULT_HPP
