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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/library.cpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/library.cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/library.cpp.dir/flags.make

CMakeFiles/library.cpp.dir/main.cpp.o: CMakeFiles/library.cpp.dir/flags.make
CMakeFiles/library.cpp.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/library.cpp.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/library.cpp.dir/main.cpp.o -c /mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1/main.cpp

CMakeFiles/library.cpp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/library.cpp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1/main.cpp > CMakeFiles/library.cpp.dir/main.cpp.i

CMakeFiles/library.cpp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/library.cpp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1/main.cpp -o CMakeFiles/library.cpp.dir/main.cpp.s

CMakeFiles/library.cpp.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/library.cpp.dir/main.cpp.o.requires

CMakeFiles/library.cpp.dir/main.cpp.o.provides: CMakeFiles/library.cpp.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/library.cpp.dir/build.make CMakeFiles/library.cpp.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/library.cpp.dir/main.cpp.o.provides

CMakeFiles/library.cpp.dir/main.cpp.o.provides.build: CMakeFiles/library.cpp.dir/main.cpp.o


# Object files for target library.cpp
library_cpp_OBJECTS = \
"CMakeFiles/library.cpp.dir/main.cpp.o"

# External object files for target library.cpp
library_cpp_EXTERNAL_OBJECTS =

library.cpp: CMakeFiles/library.cpp.dir/main.cpp.o
library.cpp: CMakeFiles/library.cpp.dir/build.make
library.cpp: CMakeFiles/library.cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable library.cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/library.cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/library.cpp.dir/build: library.cpp

.PHONY : CMakeFiles/library.cpp.dir/build

CMakeFiles/library.cpp.dir/requires: CMakeFiles/library.cpp.dir/main.cpp.o.requires

.PHONY : CMakeFiles/library.cpp.dir/requires

CMakeFiles/library.cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/library.cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/library.cpp.dir/clean

CMakeFiles/library.cpp.dir/depend:
	cd /mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1 /mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1 /mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1/cmake-build-debug /mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1/cmake-build-debug /mnt/c/Users/gsemy/OneDrive/Documents/234218/Tugy/dswet1/cmake-build-debug/CMakeFiles/library.cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/library.cpp.dir/depend
