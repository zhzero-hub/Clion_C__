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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Clion C++"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Clion C++\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/201903_4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/201903_4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/201903_4.dir/flags.make

CMakeFiles/201903_4.dir/201903_4.cpp.obj: CMakeFiles/201903_4.dir/flags.make
CMakeFiles/201903_4.dir/201903_4.cpp.obj: ../201903_4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Clion C++\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/201903_4.dir/201903_4.cpp.obj"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\201903_4.dir\201903_4.cpp.obj -c "D:\Clion C++\201903_4.cpp"

CMakeFiles/201903_4.dir/201903_4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/201903_4.dir/201903_4.cpp.i"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Clion C++\201903_4.cpp" > CMakeFiles\201903_4.dir\201903_4.cpp.i

CMakeFiles/201903_4.dir/201903_4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/201903_4.dir/201903_4.cpp.s"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Clion C++\201903_4.cpp" -o CMakeFiles\201903_4.dir\201903_4.cpp.s

# Object files for target 201903_4
201903_4_OBJECTS = \
"CMakeFiles/201903_4.dir/201903_4.cpp.obj"

# External object files for target 201903_4
201903_4_EXTERNAL_OBJECTS =

201903_4.exe: CMakeFiles/201903_4.dir/201903_4.cpp.obj
201903_4.exe: CMakeFiles/201903_4.dir/build.make
201903_4.exe: CMakeFiles/201903_4.dir/linklibs.rsp
201903_4.exe: CMakeFiles/201903_4.dir/objects1.rsp
201903_4.exe: CMakeFiles/201903_4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Clion C++\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 201903_4.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\201903_4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/201903_4.dir/build: 201903_4.exe

.PHONY : CMakeFiles/201903_4.dir/build

CMakeFiles/201903_4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\201903_4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/201903_4.dir/clean

CMakeFiles/201903_4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Clion C++" "D:\Clion C++" "D:\Clion C++\cmake-build-debug" "D:\Clion C++\cmake-build-debug" "D:\Clion C++\cmake-build-debug\CMakeFiles\201903_4.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/201903_4.dir/depend

