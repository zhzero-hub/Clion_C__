# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Clion\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Clion\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Z_HAO\CLionProjects\Clion_C__

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/testtest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testtest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testtest.dir/flags.make

CMakeFiles/testtest.dir/testtest.cpp.obj: CMakeFiles/testtest.dir/flags.make
CMakeFiles/testtest.dir/testtest.cpp.obj: ../testtest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testtest.dir/testtest.cpp.obj"
	D:\LLVM\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\testtest.dir\testtest.cpp.obj -c C:\Users\Z_HAO\CLionProjects\Clion_C__\testtest.cpp

CMakeFiles/testtest.dir/testtest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testtest.dir/testtest.cpp.i"
	D:\LLVM\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Z_HAO\CLionProjects\Clion_C__\testtest.cpp > CMakeFiles\testtest.dir\testtest.cpp.i

CMakeFiles/testtest.dir/testtest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testtest.dir/testtest.cpp.s"
	D:\LLVM\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Z_HAO\CLionProjects\Clion_C__\testtest.cpp -o CMakeFiles\testtest.dir\testtest.cpp.s

# Object files for target testtest
testtest_OBJECTS = \
"CMakeFiles/testtest.dir/testtest.cpp.obj"

# External object files for target testtest
testtest_EXTERNAL_OBJECTS =

testtest.exe: CMakeFiles/testtest.dir/testtest.cpp.obj
testtest.exe: CMakeFiles/testtest.dir/build.make
testtest.exe: CMakeFiles/testtest.dir/linklibs.rsp
testtest.exe: CMakeFiles/testtest.dir/objects1.rsp
testtest.exe: CMakeFiles/testtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testtest.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\testtest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testtest.dir/build: testtest.exe

.PHONY : CMakeFiles/testtest.dir/build

CMakeFiles/testtest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\testtest.dir\cmake_clean.cmake
.PHONY : CMakeFiles/testtest.dir/clean

CMakeFiles/testtest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Z_HAO\CLionProjects\Clion_C__ C:\Users\Z_HAO\CLionProjects\Clion_C__ C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles\testtest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testtest.dir/depend

