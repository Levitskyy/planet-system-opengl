# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/02/levickii/cg/lab5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/02/levickii/cg/lab5/build

# Utility rule file for uninstall.

# Include the progress variables for this target.
include lib/CMakeFiles/uninstall.dir/progress.make

lib/CMakeFiles/uninstall:
	cd /home/02/levickii/cg/lab5/build/lib && /usr/bin/cmake -P /home/02/levickii/cg/lab5/build/lib/cmake_uninstall.cmake

uninstall: lib/CMakeFiles/uninstall
uninstall: lib/CMakeFiles/uninstall.dir/build.make

.PHONY : uninstall

# Rule to build all files generated by this target.
lib/CMakeFiles/uninstall.dir/build: uninstall

.PHONY : lib/CMakeFiles/uninstall.dir/build

lib/CMakeFiles/uninstall.dir/clean:
	cd /home/02/levickii/cg/lab5/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/uninstall.dir/clean

lib/CMakeFiles/uninstall.dir/depend:
	cd /home/02/levickii/cg/lab5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/02/levickii/cg/lab5 /home/02/levickii/cg/deps/glfw/glfw-3.3.8 /home/02/levickii/cg/lab5/build /home/02/levickii/cg/lab5/build/lib /home/02/levickii/cg/lab5/build/lib/CMakeFiles/uninstall.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/uninstall.dir/depend

