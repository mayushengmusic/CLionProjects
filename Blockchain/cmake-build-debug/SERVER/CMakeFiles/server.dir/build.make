# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jaken/CLionProjects/Blockchain

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jaken/CLionProjects/Blockchain/cmake-build-debug

# Include any dependencies generated for this target.
include SERVER/CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include SERVER/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include SERVER/CMakeFiles/server.dir/flags.make

SERVER/CMakeFiles/server.dir/udpserver.cpp.o: SERVER/CMakeFiles/server.dir/flags.make
SERVER/CMakeFiles/server.dir/udpserver.cpp.o: ../SERVER/udpserver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaken/CLionProjects/Blockchain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object SERVER/CMakeFiles/server.dir/udpserver.cpp.o"
	cd /home/jaken/CLionProjects/Blockchain/cmake-build-debug/SERVER && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/udpserver.cpp.o -c /home/jaken/CLionProjects/Blockchain/SERVER/udpserver.cpp

SERVER/CMakeFiles/server.dir/udpserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/udpserver.cpp.i"
	cd /home/jaken/CLionProjects/Blockchain/cmake-build-debug/SERVER && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaken/CLionProjects/Blockchain/SERVER/udpserver.cpp > CMakeFiles/server.dir/udpserver.cpp.i

SERVER/CMakeFiles/server.dir/udpserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/udpserver.cpp.s"
	cd /home/jaken/CLionProjects/Blockchain/cmake-build-debug/SERVER && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaken/CLionProjects/Blockchain/SERVER/udpserver.cpp -o CMakeFiles/server.dir/udpserver.cpp.s

SERVER/CMakeFiles/server.dir/udpserver.cpp.o.requires:

.PHONY : SERVER/CMakeFiles/server.dir/udpserver.cpp.o.requires

SERVER/CMakeFiles/server.dir/udpserver.cpp.o.provides: SERVER/CMakeFiles/server.dir/udpserver.cpp.o.requires
	$(MAKE) -f SERVER/CMakeFiles/server.dir/build.make SERVER/CMakeFiles/server.dir/udpserver.cpp.o.provides.build
.PHONY : SERVER/CMakeFiles/server.dir/udpserver.cpp.o.provides

SERVER/CMakeFiles/server.dir/udpserver.cpp.o.provides.build: SERVER/CMakeFiles/server.dir/udpserver.cpp.o


# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/udpserver.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

SERVER/libserver.a: SERVER/CMakeFiles/server.dir/udpserver.cpp.o
SERVER/libserver.a: SERVER/CMakeFiles/server.dir/build.make
SERVER/libserver.a: SERVER/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jaken/CLionProjects/Blockchain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libserver.a"
	cd /home/jaken/CLionProjects/Blockchain/cmake-build-debug/SERVER && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean_target.cmake
	cd /home/jaken/CLionProjects/Blockchain/cmake-build-debug/SERVER && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
SERVER/CMakeFiles/server.dir/build: SERVER/libserver.a

.PHONY : SERVER/CMakeFiles/server.dir/build

SERVER/CMakeFiles/server.dir/requires: SERVER/CMakeFiles/server.dir/udpserver.cpp.o.requires

.PHONY : SERVER/CMakeFiles/server.dir/requires

SERVER/CMakeFiles/server.dir/clean:
	cd /home/jaken/CLionProjects/Blockchain/cmake-build-debug/SERVER && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : SERVER/CMakeFiles/server.dir/clean

SERVER/CMakeFiles/server.dir/depend:
	cd /home/jaken/CLionProjects/Blockchain/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaken/CLionProjects/Blockchain /home/jaken/CLionProjects/Blockchain/SERVER /home/jaken/CLionProjects/Blockchain/cmake-build-debug /home/jaken/CLionProjects/Blockchain/cmake-build-debug/SERVER /home/jaken/CLionProjects/Blockchain/cmake-build-debug/SERVER/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : SERVER/CMakeFiles/server.dir/depend
