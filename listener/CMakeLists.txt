cmake_minimum_required(VERSION 3.9)
project(listener)

set(CMAKE_CXX_STANDARD 11)

add_executable(listener main.cpp sha256.hpp network.hpp call_redis.hpp setmap.hpp)

target_link_libraries(listener cryptopp pthread boost_system glog cpp_redis tacopie)