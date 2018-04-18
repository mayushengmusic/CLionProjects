cmake_minimum_required(VERSION 3.7)
project(updateDNS)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp watchman.hpp exception.hpp parseconfig.hpp mysqlconnectorc.hpp)
add_executable(updateDNS ${SOURCE_FILES})
target_link_libraries(updateDNS mysqlclient)