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
include CMakeFiles/testgit.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testgit.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testgit.dir/flags.make

CMakeFiles/testgit.dir/testgit.cpp.obj: CMakeFiles/testgit.dir/flags.make
CMakeFiles/testgit.dir/testgit.cpp.obj: ../testgit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testgit.dir/testgit.cpp.obj"
	D:\LLVM\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\testgit.dir\testgit.cpp.obj -c C:\Users\Z_HAO\CLionProjects\Clion_C__\testgit.cpp

CMakeFiles/testgit.dir/testgit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testgit.dir/testgit.cpp.i"
	D:\LLVM\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Z_HAO\CLionProjects\Clion_C__\testgit.cpp > CMakeFiles\testgit.dir\testgit.cpp.i

CMakeFiles/testgit.dir/testgit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testgit.dir/testgit.cpp.s"
	D:\LLVM\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Z_HAO\CLionProjects\Clion_C__\testgit.cpp -o CMakeFiles\testgit.dir\testgit.cpp.s

# Object files for target testgit
testgit_OBJECTS = \
"CMakeFiles/testgit.dir/testgit.cpp.obj"

# External object files for target testgit
testgit_EXTERNAL_OBJECTS =

testgit.exe: CMakeFiles/testgit.dir/testgit.cpp.obj
testgit.exe: CMakeFiles/testgit.dir/build.make
testgit.exe: CMakeFiles/testgit.dir/linklibs.rsp
testgit.exe: CMakeFiles/testgit.dir/objects1.rsp
testgit.exe: CMakeFiles/testgit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testgit.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\testgit.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testgit.dir/build: testgit.exe

.PHONY : CMakeFiles/testgit.dir/build

CMakeFiles/testgit.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\testgit.dir\cmake_clean.cmake
.PHONY : CMakeFiles/testgit.dir/clean

CMakeFiles/testgit.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Z_HAO\CLionProjects\Clion_C__ C:\Users\Z_HAO\CLionProjects\Clion_C__ C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles\testgit.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testgit.dir/depend
