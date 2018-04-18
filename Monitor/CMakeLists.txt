cmake_minimum_required(VERSION 3.9)
project(Monitor)

set(CMAKE_CXX_STANDARD 14)

add_executable(Monitor src/main.cpp src/network.cpp src/include/network.hpp src/processcmdbypstream.cpp src/include/processcmdbypstream.hpp)
target_link_libraries(Monitor boost_system pthread glog)

