cmake_minimum_required(VERSION 3.9)
project(FUCKSOCK)

set(CMAKE_CXX_STANDARD 11)

add_executable(fuckcode main.cpp callredis.hpp server.hpp)
target_link_libraries(fuckcode  pthread boost_system boost_filesystem cpp_redis tacopie)