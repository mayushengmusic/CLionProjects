cmake_minimum_required(VERSION 3.9)
project(gosend)

set(CMAKE_CXX_STANDARD 11)

add_executable(gosend main.cpp sha256.hpp network.hpp readcommand.hpp json.hpp)
target_link_libraries(gosend cryptopp pthread boost_date_time boost_system glog)