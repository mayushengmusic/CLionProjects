cmake_minimum_required(VERSION 3.9)
project(BlockChainDemo)

set(CMAKE_CXX_STANDARD 14)

add_executable(nms main.cpp ecdsa.hpp SHA256.hpp block.pb.cc block.pb.h collection.hpp sendtrans.hpp netservice.hpp miner.hpp serverthread.hpp)
target_link_libraries(nms cryptopp boost_system boost_regex protobuf boost_thread-mt)