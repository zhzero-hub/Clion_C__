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
include CMakeFiles/201909_5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/201909_5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/201909_5.dir/flags.make

CMakeFiles/201909_5.dir/201909_5.cpp.obj: CMakeFiles/201909_5.dir/flags.make
CMakeFiles/201909_5.dir/201909_5.cpp.obj: ../201909_5.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/201909_5.dir/201909_5.cpp.obj"
	D:\LLVM\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\201909_5.dir\201909_5.cpp.obj -c C:\Users\Z_HAO\CLionProjects\Clion_C__\201909_5.cpp

CMakeFiles/201909_5.dir/201909_5.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/201909_5.dir/201909_5.cpp.i"
	D:\LLVM\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Z_HAO\CLionProjects\Clion_C__\201909_5.cpp > CMakeFiles\201909_5.dir\201909_5.cpp.i

CMakeFiles/201909_5.dir/201909_5.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/201909_5.dir/201909_5.cpp.s"
	D:\LLVM\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Z_HAO\CLionProjects\Clion_C__\201909_5.cpp -o CMakeFiles\201909_5.dir\201909_5.cpp.s

# Object files for target 201909_5
201909_5_OBJECTS = \
"CMakeFiles/201909_5.dir/201909_5.cpp.obj"

# External object files for target 201909_5
201909_5_EXTERNAL_OBJECTS =

201909_5.exe: CMakeFiles/201909_5.dir/201909_5.cpp.obj
201909_5.exe: CMakeFiles/201909_5.dir/build.make
201909_5.exe: CMakeFiles/201909_5.dir/linklibs.rsp
201909_5.exe: CMakeFiles/201909_5.dir/objects1.rsp
201909_5.exe: CMakeFiles/201909_5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 201909_5.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\201909_5.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/201909_5.dir/build: 201909_5.exe

.PHONY : CMakeFiles/201909_5.dir/build

CMakeFiles/201909_5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\201909_5.dir\cmake_clean.cmake
.PHONY : CMakeFiles/201909_5.dir/clean

CMakeFiles/201909_5.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Z_HAO\CLionProjects\Clion_C__ C:\Users\Z_HAO\CLionProjects\Clion_C__ C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles\201909_5.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/201909_5.dir/depend

