cmake_minimum_required(VERSION 3.6)
project(OpencvStudy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package( OpenCV REQUIRED )
set(SOURCE_FILES main.cpp ClassOne.hpp)
add_executable(OpencvStudy ${SOURCE_FILES})
target_link_libraries( OpencvStudy ${OpenCV_LIBS} )