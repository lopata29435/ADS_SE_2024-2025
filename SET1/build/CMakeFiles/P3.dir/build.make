# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = D:/SE/Makers/Cmake/bin/cmake.exe

# The command to remove a file.
RM = D:/SE/Makers/Cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/Projects/VScodeCXX/ADS/SET1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/Projects/VScodeCXX/ADS/SET1/build

# Include any dependencies generated for this target.
include CMakeFiles/P3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/P3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/P3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/P3.dir/flags.make

CMakeFiles/P3.dir/P3/main.cpp.obj: CMakeFiles/P3.dir/flags.make
CMakeFiles/P3.dir/P3/main.cpp.obj: D:/Projects/VScodeCXX/ADS/SET1/P3/main.cpp
CMakeFiles/P3.dir/P3/main.cpp.obj: CMakeFiles/P3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/Projects/VScodeCXX/ADS/SET1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/P3.dir/P3/main.cpp.obj"
	D:/SE/Compilers/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P3.dir/P3/main.cpp.obj -MF CMakeFiles/P3.dir/P3/main.cpp.obj.d -o CMakeFiles/P3.dir/P3/main.cpp.obj -c D:/Projects/VScodeCXX/ADS/SET1/P3/main.cpp

CMakeFiles/P3.dir/P3/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/P3.dir/P3/main.cpp.i"
	D:/SE/Compilers/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/Projects/VScodeCXX/ADS/SET1/P3/main.cpp > CMakeFiles/P3.dir/P3/main.cpp.i

CMakeFiles/P3.dir/P3/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/P3.dir/P3/main.cpp.s"
	D:/SE/Compilers/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/Projects/VScodeCXX/ADS/SET1/P3/main.cpp -o CMakeFiles/P3.dir/P3/main.cpp.s

# Object files for target P3
P3_OBJECTS = \
"CMakeFiles/P3.dir/P3/main.cpp.obj"

# External object files for target P3
P3_EXTERNAL_OBJECTS =

P3.exe: CMakeFiles/P3.dir/P3/main.cpp.obj
P3.exe: CMakeFiles/P3.dir/build.make
P3.exe: CMakeFiles/P3.dir/linkLibs.rsp
P3.exe: CMakeFiles/P3.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/Projects/VScodeCXX/ADS/SET1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable P3.exe"
	D:/SE/Makers/Cmake/bin/cmake.exe -E rm -f CMakeFiles/P3.dir/objects.a
	D:/SE/Compilers/w64devkit/bin/ar.exe qc CMakeFiles/P3.dir/objects.a @CMakeFiles/P3.dir/objects1.rsp
	D:/SE/Compilers/w64devkit/bin/g++.exe -g -O0 -Wall -Wl,--whole-archive CMakeFiles/P3.dir/objects.a -Wl,--no-whole-archive -o P3.exe -Wl,--out-implib,libP3.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/P3.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/P3.dir/build: P3.exe
.PHONY : CMakeFiles/P3.dir/build

CMakeFiles/P3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/P3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/P3.dir/clean

CMakeFiles/P3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Projects/VScodeCXX/ADS/SET1 D:/Projects/VScodeCXX/ADS/SET1 D:/Projects/VScodeCXX/ADS/SET1/build D:/Projects/VScodeCXX/ADS/SET1/build D:/Projects/VScodeCXX/ADS/SET1/build/CMakeFiles/P3.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/P3.dir/depend

