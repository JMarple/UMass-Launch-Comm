# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/jmarple/code/mavlink

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jmarple/code/UMass-Launch-Comm/mavlink-build

# Utility rule file for minimal.xml-v0.9.

# Include the progress variables for this target.
include CMakeFiles/minimal.xml-v0.9.dir/progress.make

CMakeFiles/minimal.xml-v0.9: minimal.xml-v0.9-stamp

minimal.xml-v0.9-stamp:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jmarple/code/UMass-Launch-Comm/mavlink-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating minimal.xml-v0.9-stamp"
	PYTHONPATH=:/home/jmarple/code/mavlink /usr/bin/python -m pymavlink.tools.mavgen --lang=C --wire-protocol=0.9 --output=include/v0.9 /home/jmarple/code/mavlink/message_definitions/v0.9/minimal.xml
	touch minimal.xml-v0.9-stamp

minimal.xml-v0.9: CMakeFiles/minimal.xml-v0.9
minimal.xml-v0.9: minimal.xml-v0.9-stamp
minimal.xml-v0.9: CMakeFiles/minimal.xml-v0.9.dir/build.make
.PHONY : minimal.xml-v0.9

# Rule to build all files generated by this target.
CMakeFiles/minimal.xml-v0.9.dir/build: minimal.xml-v0.9
.PHONY : CMakeFiles/minimal.xml-v0.9.dir/build

CMakeFiles/minimal.xml-v0.9.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/minimal.xml-v0.9.dir/cmake_clean.cmake
.PHONY : CMakeFiles/minimal.xml-v0.9.dir/clean

CMakeFiles/minimal.xml-v0.9.dir/depend:
	cd /home/jmarple/code/UMass-Launch-Comm/mavlink-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jmarple/code/mavlink /home/jmarple/code/mavlink /home/jmarple/code/UMass-Launch-Comm/mavlink-build /home/jmarple/code/UMass-Launch-Comm/mavlink-build /home/jmarple/code/UMass-Launch-Comm/mavlink-build/CMakeFiles/minimal.xml-v0.9.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minimal.xml-v0.9.dir/depend

