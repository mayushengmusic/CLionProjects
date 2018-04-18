cmake_minimum_required(VERSION 3.9)
project(TESTCRYPTOPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(TESTCRYPTOPP ecdsa.hpp main.cpp SHA256.hpp)
target_link_libraries(TESTCRYPTOPP cryptopp)