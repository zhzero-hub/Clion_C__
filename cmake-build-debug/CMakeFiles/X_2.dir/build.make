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
include CMakeFiles/X_2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/X_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/X_2.dir/flags.make

CMakeFiles/X_2.dir/X_2.cpp.obj: CMakeFiles/X_2.dir/flags.make
CMakeFiles/X_2.dir/X_2.cpp.obj: ../X_2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/X_2.dir/X_2.cpp.obj"
	D:\LLVM\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\X_2.dir\X_2.cpp.obj -c C:\Users\Z_HAO\CLionProjects\Clion_C__\X_2.cpp

CMakeFiles/X_2.dir/X_2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/X_2.dir/X_2.cpp.i"
	D:\LLVM\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Z_HAO\CLionProjects\Clion_C__\X_2.cpp > CMakeFiles\X_2.dir\X_2.cpp.i

CMakeFiles/X_2.dir/X_2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/X_2.dir/X_2.cpp.s"
	D:\LLVM\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Z_HAO\CLionProjects\Clion_C__\X_2.cpp -o CMakeFiles\X_2.dir\X_2.cpp.s

# Object files for target X_2
X_2_OBJECTS = \
"CMakeFiles/X_2.dir/X_2.cpp.obj"

# External object files for target X_2
X_2_EXTERNAL_OBJECTS =

X_2.exe: CMakeFiles/X_2.dir/X_2.cpp.obj
X_2.exe: CMakeFiles/X_2.dir/build.make
X_2.exe: CMakeFiles/X_2.dir/linklibs.rsp
X_2.exe: CMakeFiles/X_2.dir/objects1.rsp
X_2.exe: CMakeFiles/X_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable X_2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\X_2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/X_2.dir/build: X_2.exe

.PHONY : CMakeFiles/X_2.dir/build

CMakeFiles/X_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\X_2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/X_2.dir/clean

CMakeFiles/X_2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Z_HAO\CLionProjects\Clion_C__ C:\Users\Z_HAO\CLionProjects\Clion_C__ C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles\X_2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/X_2.dir/depend

