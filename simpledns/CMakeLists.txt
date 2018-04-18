cmake_minimum_required(VERSION 3.6)
project(simpledns)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/main.cpp
        src/buffer.cpp
        src/message.cpp
        src/qs.cpp
        src/rr.cpp
        src/include/udp_server.hpp
        src/include/buffer.h
        src/include/qs.h
        src/include/rr.h
        src/include/message.h
        src/include/dns.h
        src/include/exception.h
        src/include/udp_client.hpp
        src/include/mysqlconnectorc.hpp
        src/include/callbackmysql.hpp src/include/parseconfig.hpp)


add_executable(simpledns ${SOURCE_FILES})
target_link_libraries(simpledns mysqlclient)

