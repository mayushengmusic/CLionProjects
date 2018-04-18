cmake_minimum_required(VERSION 3.6)
project(NETCapture)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp CompBuf.hpp MySqlWriter.hpp packet.hpp)
link_directories("/usr/local/lib/mysql")
add_executable(NETCapture ${SOURCE_FILES})
target_link_libraries(NETCapture mysqlcppconn)
target_link_libraries(NETCapture pthread)
target_link_libraries(NETCapture pcap)