# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_SOURCE_DIR = /home/jaken/CLionProjects/makelabel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jaken/CLionProjects/makelabel/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/makelabel.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/makelabel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/makelabel.dir/flags.make

CMakeFiles/makelabel.dir/main.cpp.o: CMakeFiles/makelabel.dir/flags.make
CMakeFiles/makelabel.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaken/CLionProjects/makelabel/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/makelabel.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/makelabel.dir/main.cpp.o -c /home/jaken/CLionProjects/makelabel/main.cpp

CMakeFiles/makelabel.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/makelabel.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaken/CLionProjects/makelabel/main.cpp > CMakeFiles/makelabel.dir/main.cpp.i

CMakeFiles/makelabel.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/makelabel.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaken/CLionProjects/makelabel/main.cpp -o CMakeFiles/makelabel.dir/main.cpp.s

CMakeFiles/makelabel.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/makelabel.dir/main.cpp.o.requires

CMakeFiles/makelabel.dir/main.cpp.o.provides: CMakeFiles/makelabel.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/makelabel.dir/build.make CMakeFiles/makelabel.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/makelabel.dir/main.cpp.o.provides

CMakeFiles/makelabel.dir/main.cpp.o.provides.build: CMakeFiles/makelabel.dir/main.cpp.o


# Object files for target makelabel
makelabel_OBJECTS = \
"CMakeFiles/makelabel.dir/main.cpp.o"

# External object files for target makelabel
makelabel_EXTERNAL_OBJECTS =

makelabel: CMakeFiles/makelabel.dir/main.cpp.o
makelabel: CMakeFiles/makelabel.dir/build.make
makelabel: CMakeFiles/makelabel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jaken/CLionProjects/makelabel/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable makelabel"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/makelabel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/makelabel.dir/build: makelabel

.PHONY : CMakeFiles/makelabel.dir/build

CMakeFiles/makelabel.dir/requires: CMakeFiles/makelabel.dir/main.cpp.o.requires

.PHONY : CMakeFiles/makelabel.dir/requires

CMakeFiles/makelabel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/makelabel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/makelabel.dir/clean

CMakeFiles/makelabel.dir/depend:
	cd /home/jaken/CLionProjects/makelabel/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaken/CLionProjects/makelabel /home/jaken/CLionProjects/makelabel /home/jaken/CLionProjects/makelabel/cmake-build-debug /home/jaken/CLionProjects/makelabel/cmake-build-debug /home/jaken/CLionProjects/makelabel/cmake-build-debug/CMakeFiles/makelabel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/makelabel.dir/depend

