cmake_minimum_required(VERSION 3.2)
project(Blockchain)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_STANDARD 14)



add_subdirectory(DNS)
add_subdirectory(PARSEDNS)
add_subdirectory(SERVER)


aux_source_directory(. SOURCE_FILES)
add_executable(Blockchain ${SOURCE_FILES})
target_link_libraries(Blockchain dns parsedns server boost_system pthread)
