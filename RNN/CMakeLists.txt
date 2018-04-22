cmake_minimum_required(VERSION 3.10)
project(RNN)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(. SRC)
add_executable(RNN main.cpp lstm.hpp huawei.hpp GlobalMacro.hpp)