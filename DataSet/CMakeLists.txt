cmake_minimum_required(VERSION 3.6)
project(DataSet)

set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )

set(SOURCE_FILES main.cpp getminist.hpp stick.hpp)
add_executable(DataSet ${SOURCE_FILES})
target_link_libraries(DataSet ${OpenCV_LIBS} )
target_link_libraries(DataSet pthread)