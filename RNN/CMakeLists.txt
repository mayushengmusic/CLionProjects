cmake_minimum_required(VERSION 3.10)
project(RNN)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0  -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 ")
aux_source_directory(. SRC)
add_executable(RNN main.cpp lstm.hpp huawei.hpp GlobalMacro.hpp datapreprocess.hpp)