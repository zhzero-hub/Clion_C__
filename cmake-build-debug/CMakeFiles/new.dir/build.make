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
include CMakeFiles/new.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/new.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/new.dir/flags.make

CMakeFiles/new.dir/new.cpp.obj: CMakeFiles/new.dir/flags.make
CMakeFiles/new.dir/new.cpp.obj: ../new.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/new.dir/new.cpp.obj"
	D:\LLVM\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\new.dir\new.cpp.obj -c C:\Users\Z_HAO\CLionProjects\Clion_C__\new.cpp

CMakeFiles/new.dir/new.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/new.dir/new.cpp.i"
	D:\LLVM\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Z_HAO\CLionProjects\Clion_C__\new.cpp > CMakeFiles\new.dir\new.cpp.i

CMakeFiles/new.dir/new.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/new.dir/new.cpp.s"
	D:\LLVM\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Z_HAO\CLionProjects\Clion_C__\new.cpp -o CMakeFiles\new.dir\new.cpp.s

# Object files for target new
new_OBJECTS = \
"CMakeFiles/new.dir/new.cpp.obj"

# External object files for target new
new_EXTERNAL_OBJECTS =

new.exe: CMakeFiles/new.dir/new.cpp.obj
new.exe: CMakeFiles/new.dir/build.make
new.exe: CMakeFiles/new.dir/linklibs.rsp
new.exe: CMakeFiles/new.dir/objects1.rsp
new.exe: CMakeFiles/new.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable new.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\new.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/new.dir/build: new.exe

.PHONY : CMakeFiles/new.dir/build

CMakeFiles/new.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\new.dir\cmake_clean.cmake
.PHONY : CMakeFiles/new.dir/clean

CMakeFiles/new.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Z_HAO\CLionProjects\Clion_C__ C:\Users\Z_HAO\CLionProjects\Clion_C__ C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug C:\Users\Z_HAO\CLionProjects\Clion_C__\cmake-build-debug\CMakeFiles\new.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/new.dir/depend

