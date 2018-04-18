cmake_minimum_required(VERSION 3.8)
project(Hurricane)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp API/ITask.hpp API/ISpout.hpp API/IBolt.hpp API/OutputCollector.hpp)
add_executable(Hurricane ${SOURCE_FILES})