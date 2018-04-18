cmake_minimum_required(VERSION 3.4)
project(robot)

set(CMAKE_CXX_STANDARD 11)

add_executable(robot main.cpp json.hpp root_certificates.hpp)

target_link_libraries(robot pthread boost_system boost_filesystem ssl crypto)