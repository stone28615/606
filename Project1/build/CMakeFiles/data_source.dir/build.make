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
CMAKE_SOURCE_DIR = /home/brushstone/Desktop/606/Project1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brushstone/Desktop/606/Project1/build

# Include any dependencies generated for this target.
include CMakeFiles/data_source.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/data_source.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/data_source.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/data_source.dir/flags.make

CMakeFiles/data_source.dir/data_source.cpp.o: CMakeFiles/data_source.dir/flags.make
CMakeFiles/data_source.dir/data_source.cpp.o: ../data_source.cpp
CMakeFiles/data_source.dir/data_source.cpp.o: CMakeFiles/data_source.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brushstone/Desktop/606/Project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/data_source.dir/data_source.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/data_source.dir/data_source.cpp.o -MF CMakeFiles/data_source.dir/data_source.cpp.o.d -o CMakeFiles/data_source.dir/data_source.cpp.o -c /home/brushstone/Desktop/606/Project1/data_source.cpp

CMakeFiles/data_source.dir/data_source.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/data_source.dir/data_source.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brushstone/Desktop/606/Project1/data_source.cpp > CMakeFiles/data_source.dir/data_source.cpp.i

CMakeFiles/data_source.dir/data_source.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/data_source.dir/data_source.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brushstone/Desktop/606/Project1/data_source.cpp -o CMakeFiles/data_source.dir/data_source.cpp.s

# Object files for target data_source
data_source_OBJECTS = \
"CMakeFiles/data_source.dir/data_source.cpp.o"

# External object files for target data_source
data_source_EXTERNAL_OBJECTS =

data_source: CMakeFiles/data_source.dir/data_source.cpp.o
data_source: CMakeFiles/data_source.dir/build.make
data_source: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
data_source: CMakeFiles/data_source.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brushstone/Desktop/606/Project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable data_source"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/data_source.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/data_source.dir/build: data_source
.PHONY : CMakeFiles/data_source.dir/build

CMakeFiles/data_source.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/data_source.dir/cmake_clean.cmake
.PHONY : CMakeFiles/data_source.dir/clean

CMakeFiles/data_source.dir/depend:
	cd /home/brushstone/Desktop/606/Project1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brushstone/Desktop/606/Project1 /home/brushstone/Desktop/606/Project1 /home/brushstone/Desktop/606/Project1/build /home/brushstone/Desktop/606/Project1/build /home/brushstone/Desktop/606/Project1/build/CMakeFiles/data_source.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/data_source.dir/depend

