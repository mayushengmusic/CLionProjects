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
CMAKE_COMMAND = /usr/local/share/clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /usr/local/share/clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jaken/CLionProjects/simpledns

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jaken/CLionProjects/simpledns/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/simpledns.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/simpledns.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simpledns.dir/flags.make

CMakeFiles/simpledns.dir/src/main.cpp.o: CMakeFiles/simpledns.dir/flags.make
CMakeFiles/simpledns.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaken/CLionProjects/simpledns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simpledns.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpledns.dir/src/main.cpp.o -c /home/jaken/CLionProjects/simpledns/src/main.cpp

CMakeFiles/simpledns.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpledns.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaken/CLionProjects/simpledns/src/main.cpp > CMakeFiles/simpledns.dir/src/main.cpp.i

CMakeFiles/simpledns.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpledns.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaken/CLionProjects/simpledns/src/main.cpp -o CMakeFiles/simpledns.dir/src/main.cpp.s

CMakeFiles/simpledns.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/simpledns.dir/src/main.cpp.o.requires

CMakeFiles/simpledns.dir/src/main.cpp.o.provides: CMakeFiles/simpledns.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/simpledns.dir/build.make CMakeFiles/simpledns.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/simpledns.dir/src/main.cpp.o.provides

CMakeFiles/simpledns.dir/src/main.cpp.o.provides.build: CMakeFiles/simpledns.dir/src/main.cpp.o


CMakeFiles/simpledns.dir/src/buffer.cpp.o: CMakeFiles/simpledns.dir/flags.make
CMakeFiles/simpledns.dir/src/buffer.cpp.o: ../src/buffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaken/CLionProjects/simpledns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/simpledns.dir/src/buffer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpledns.dir/src/buffer.cpp.o -c /home/jaken/CLionProjects/simpledns/src/buffer.cpp

CMakeFiles/simpledns.dir/src/buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpledns.dir/src/buffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaken/CLionProjects/simpledns/src/buffer.cpp > CMakeFiles/simpledns.dir/src/buffer.cpp.i

CMakeFiles/simpledns.dir/src/buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpledns.dir/src/buffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaken/CLionProjects/simpledns/src/buffer.cpp -o CMakeFiles/simpledns.dir/src/buffer.cpp.s

CMakeFiles/simpledns.dir/src/buffer.cpp.o.requires:

.PHONY : CMakeFiles/simpledns.dir/src/buffer.cpp.o.requires

CMakeFiles/simpledns.dir/src/buffer.cpp.o.provides: CMakeFiles/simpledns.dir/src/buffer.cpp.o.requires
	$(MAKE) -f CMakeFiles/simpledns.dir/build.make CMakeFiles/simpledns.dir/src/buffer.cpp.o.provides.build
.PHONY : CMakeFiles/simpledns.dir/src/buffer.cpp.o.provides

CMakeFiles/simpledns.dir/src/buffer.cpp.o.provides.build: CMakeFiles/simpledns.dir/src/buffer.cpp.o


CMakeFiles/simpledns.dir/src/message.cpp.o: CMakeFiles/simpledns.dir/flags.make
CMakeFiles/simpledns.dir/src/message.cpp.o: ../src/message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaken/CLionProjects/simpledns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/simpledns.dir/src/message.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpledns.dir/src/message.cpp.o -c /home/jaken/CLionProjects/simpledns/src/message.cpp

CMakeFiles/simpledns.dir/src/message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpledns.dir/src/message.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaken/CLionProjects/simpledns/src/message.cpp > CMakeFiles/simpledns.dir/src/message.cpp.i

CMakeFiles/simpledns.dir/src/message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpledns.dir/src/message.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaken/CLionProjects/simpledns/src/message.cpp -o CMakeFiles/simpledns.dir/src/message.cpp.s

CMakeFiles/simpledns.dir/src/message.cpp.o.requires:

.PHONY : CMakeFiles/simpledns.dir/src/message.cpp.o.requires

CMakeFiles/simpledns.dir/src/message.cpp.o.provides: CMakeFiles/simpledns.dir/src/message.cpp.o.requires
	$(MAKE) -f CMakeFiles/simpledns.dir/build.make CMakeFiles/simpledns.dir/src/message.cpp.o.provides.build
.PHONY : CMakeFiles/simpledns.dir/src/message.cpp.o.provides

CMakeFiles/simpledns.dir/src/message.cpp.o.provides.build: CMakeFiles/simpledns.dir/src/message.cpp.o


CMakeFiles/simpledns.dir/src/qs.cpp.o: CMakeFiles/simpledns.dir/flags.make
CMakeFiles/simpledns.dir/src/qs.cpp.o: ../src/qs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaken/CLionProjects/simpledns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/simpledns.dir/src/qs.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpledns.dir/src/qs.cpp.o -c /home/jaken/CLionProjects/simpledns/src/qs.cpp

CMakeFiles/simpledns.dir/src/qs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpledns.dir/src/qs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaken/CLionProjects/simpledns/src/qs.cpp > CMakeFiles/simpledns.dir/src/qs.cpp.i

CMakeFiles/simpledns.dir/src/qs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpledns.dir/src/qs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaken/CLionProjects/simpledns/src/qs.cpp -o CMakeFiles/simpledns.dir/src/qs.cpp.s

CMakeFiles/simpledns.dir/src/qs.cpp.o.requires:

.PHONY : CMakeFiles/simpledns.dir/src/qs.cpp.o.requires

CMakeFiles/simpledns.dir/src/qs.cpp.o.provides: CMakeFiles/simpledns.dir/src/qs.cpp.o.requires
	$(MAKE) -f CMakeFiles/simpledns.dir/build.make CMakeFiles/simpledns.dir/src/qs.cpp.o.provides.build
.PHONY : CMakeFiles/simpledns.dir/src/qs.cpp.o.provides

CMakeFiles/simpledns.dir/src/qs.cpp.o.provides.build: CMakeFiles/simpledns.dir/src/qs.cpp.o


CMakeFiles/simpledns.dir/src/rr.cpp.o: CMakeFiles/simpledns.dir/flags.make
CMakeFiles/simpledns.dir/src/rr.cpp.o: ../src/rr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaken/CLionProjects/simpledns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/simpledns.dir/src/rr.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simpledns.dir/src/rr.cpp.o -c /home/jaken/CLionProjects/simpledns/src/rr.cpp

CMakeFiles/simpledns.dir/src/rr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpledns.dir/src/rr.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaken/CLionProjects/simpledns/src/rr.cpp > CMakeFiles/simpledns.dir/src/rr.cpp.i

CMakeFiles/simpledns.dir/src/rr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpledns.dir/src/rr.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaken/CLionProjects/simpledns/src/rr.cpp -o CMakeFiles/simpledns.dir/src/rr.cpp.s

CMakeFiles/simpledns.dir/src/rr.cpp.o.requires:

.PHONY : CMakeFiles/simpledns.dir/src/rr.cpp.o.requires

CMakeFiles/simpledns.dir/src/rr.cpp.o.provides: CMakeFiles/simpledns.dir/src/rr.cpp.o.requires
	$(MAKE) -f CMakeFiles/simpledns.dir/build.make CMakeFiles/simpledns.dir/src/rr.cpp.o.provides.build
.PHONY : CMakeFiles/simpledns.dir/src/rr.cpp.o.provides

CMakeFiles/simpledns.dir/src/rr.cpp.o.provides.build: CMakeFiles/simpledns.dir/src/rr.cpp.o


# Object files for target simpledns
simpledns_OBJECTS = \
"CMakeFiles/simpledns.dir/src/main.cpp.o" \
"CMakeFiles/simpledns.dir/src/buffer.cpp.o" \
"CMakeFiles/simpledns.dir/src/message.cpp.o" \
"CMakeFiles/simpledns.dir/src/qs.cpp.o" \
"CMakeFiles/simpledns.dir/src/rr.cpp.o"

# External object files for target simpledns
simpledns_EXTERNAL_OBJECTS =

simpledns: CMakeFiles/simpledns.dir/src/main.cpp.o
simpledns: CMakeFiles/simpledns.dir/src/buffer.cpp.o
simpledns: CMakeFiles/simpledns.dir/src/message.cpp.o
simpledns: CMakeFiles/simpledns.dir/src/qs.cpp.o
simpledns: CMakeFiles/simpledns.dir/src/rr.cpp.o
simpledns: CMakeFiles/simpledns.dir/build.make
simpledns: CMakeFiles/simpledns.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jaken/CLionProjects/simpledns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable simpledns"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simpledns.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simpledns.dir/build: simpledns

.PHONY : CMakeFiles/simpledns.dir/build

CMakeFiles/simpledns.dir/requires: CMakeFiles/simpledns.dir/src/main.cpp.o.requires
CMakeFiles/simpledns.dir/requires: CMakeFiles/simpledns.dir/src/buffer.cpp.o.requires
CMakeFiles/simpledns.dir/requires: CMakeFiles/simpledns.dir/src/message.cpp.o.requires
CMakeFiles/simpledns.dir/requires: CMakeFiles/simpledns.dir/src/qs.cpp.o.requires
CMakeFiles/simpledns.dir/requires: CMakeFiles/simpledns.dir/src/rr.cpp.o.requires

.PHONY : CMakeFiles/simpledns.dir/requires

CMakeFiles/simpledns.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simpledns.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simpledns.dir/clean

CMakeFiles/simpledns.dir/depend:
	cd /home/jaken/CLionProjects/simpledns/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaken/CLionProjects/simpledns /home/jaken/CLionProjects/simpledns /home/jaken/CLionProjects/simpledns/cmake-build-debug /home/jaken/CLionProjects/simpledns/cmake-build-debug /home/jaken/CLionProjects/simpledns/cmake-build-debug/CMakeFiles/simpledns.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simpledns.dir/depend
