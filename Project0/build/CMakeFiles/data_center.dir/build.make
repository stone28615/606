# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/brushstone/Desktop/606/Project0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brushstone/Desktop/606/Project0/build

# Include any dependencies generated for this target.
include CMakeFiles/data_center.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/data_center.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/data_center.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/data_center.dir/flags.make

CMakeFiles/data_center.dir/data_center.cpp.o: CMakeFiles/data_center.dir/flags.make
CMakeFiles/data_center.dir/data_center.cpp.o: ../data_center.cpp
CMakeFiles/data_center.dir/data_center.cpp.o: CMakeFiles/data_center.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brushstone/Desktop/606/Project0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/data_center.dir/data_center.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/data_center.dir/data_center.cpp.o -MF CMakeFiles/data_center.dir/data_center.cpp.o.d -o CMakeFiles/data_center.dir/data_center.cpp.o -c /home/brushstone/Desktop/606/Project0/data_center.cpp

CMakeFiles/data_center.dir/data_center.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/data_center.dir/data_center.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brushstone/Desktop/606/Project0/data_center.cpp > CMakeFiles/data_center.dir/data_center.cpp.i

CMakeFiles/data_center.dir/data_center.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/data_center.dir/data_center.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brushstone/Desktop/606/Project0/data_center.cpp -o CMakeFiles/data_center.dir/data_center.cpp.s

# Object files for target data_center
data_center_OBJECTS = \
"CMakeFiles/data_center.dir/data_center.cpp.o"

# External object files for target data_center
data_center_EXTERNAL_OBJECTS =

data_center: CMakeFiles/data_center.dir/data_center.cpp.o
data_center: CMakeFiles/data_center.dir/build.make
data_center: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
data_center: CMakeFiles/data_center.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brushstone/Desktop/606/Project0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable data_center"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/data_center.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/data_center.dir/build: data_center
.PHONY : CMakeFiles/data_center.dir/build

CMakeFiles/data_center.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/data_center.dir/cmake_clean.cmake
.PHONY : CMakeFiles/data_center.dir/clean

CMakeFiles/data_center.dir/depend:
	cd /home/brushstone/Desktop/606/Project0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brushstone/Desktop/606/Project0 /home/brushstone/Desktop/606/Project0 /home/brushstone/Desktop/606/Project0/build /home/brushstone/Desktop/606/Project0/build /home/brushstone/Desktop/606/Project0/build/CMakeFiles/data_center.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/data_center.dir/depend

