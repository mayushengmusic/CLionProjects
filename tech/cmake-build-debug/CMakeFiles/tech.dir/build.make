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
CMAKE_SOURCE_DIR = /home/jaken/CLionProjects/tech

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jaken/CLionProjects/tech/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tech.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tech.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tech.dir/flags.make

CMakeFiles/tech.dir/main.cpp.o: CMakeFiles/tech.dir/flags.make
CMakeFiles/tech.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaken/CLionProjects/tech/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tech.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tech.dir/main.cpp.o -c /home/jaken/CLionProjects/tech/main.cpp

CMakeFiles/tech.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tech.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaken/CLionProjects/tech/main.cpp > CMakeFiles/tech.dir/main.cpp.i

CMakeFiles/tech.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tech.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaken/CLionProjects/tech/main.cpp -o CMakeFiles/tech.dir/main.cpp.s

CMakeFiles/tech.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/tech.dir/main.cpp.o.requires

CMakeFiles/tech.dir/main.cpp.o.provides: CMakeFiles/tech.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/tech.dir/build.make CMakeFiles/tech.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/tech.dir/main.cpp.o.provides

CMakeFiles/tech.dir/main.cpp.o.provides.build: CMakeFiles/tech.dir/main.cpp.o


# Object files for target tech
tech_OBJECTS = \
"CMakeFiles/tech.dir/main.cpp.o"

# External object files for target tech
tech_EXTERNAL_OBJECTS =

tech: CMakeFiles/tech.dir/main.cpp.o
tech: CMakeFiles/tech.dir/build.make
tech: CMakeFiles/tech.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jaken/CLionProjects/tech/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tech"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tech.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tech.dir/build: tech

.PHONY : CMakeFiles/tech.dir/build

CMakeFiles/tech.dir/requires: CMakeFiles/tech.dir/main.cpp.o.requires

.PHONY : CMakeFiles/tech.dir/requires

CMakeFiles/tech.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tech.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tech.dir/clean

CMakeFiles/tech.dir/depend:
	cd /home/jaken/CLionProjects/tech/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaken/CLionProjects/tech /home/jaken/CLionProjects/tech /home/jaken/CLionProjects/tech/cmake-build-debug /home/jaken/CLionProjects/tech/cmake-build-debug /home/jaken/CLionProjects/tech/cmake-build-debug/CMakeFiles/tech.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tech.dir/depend
