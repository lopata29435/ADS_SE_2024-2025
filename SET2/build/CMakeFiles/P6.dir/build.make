# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = E:\Programs\QT\Tools\CMake_64\bin\cmake.exe

# The command to remove a file.
RM = E:\Programs\QT\Tools\CMake_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Projects\VScodeCXX\ADS\SET2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Projects\VScodeCXX\ADS\SET2\build

# Include any dependencies generated for this target.
include CMakeFiles/P6.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/P6.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/P6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/P6.dir/flags.make

CMakeFiles/P6.dir/P6/main.cpp.obj: CMakeFiles/P6.dir/flags.make
CMakeFiles/P6.dir/P6/main.cpp.obj: D:/Projects/VScodeCXX/ADS/SET2/P6/main.cpp
CMakeFiles/P6.dir/P6/main.cpp.obj: CMakeFiles/P6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Projects\VScodeCXX\ADS\SET2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/P6.dir/P6/main.cpp.obj"
	E:\Programs\QT\Tools\mingw1310_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/P6.dir/P6/main.cpp.obj -MF CMakeFiles\P6.dir\P6\main.cpp.obj.d -o CMakeFiles\P6.dir\P6\main.cpp.obj -c D:\Projects\VScodeCXX\ADS\SET2\P6\main.cpp

CMakeFiles/P6.dir/P6/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/P6.dir/P6/main.cpp.i"
	E:\Programs\QT\Tools\mingw1310_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\VScodeCXX\ADS\SET2\P6\main.cpp > CMakeFiles\P6.dir\P6\main.cpp.i

CMakeFiles/P6.dir/P6/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/P6.dir/P6/main.cpp.s"
	E:\Programs\QT\Tools\mingw1310_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\VScodeCXX\ADS\SET2\P6\main.cpp -o CMakeFiles\P6.dir\P6\main.cpp.s

# Object files for target P6
P6_OBJECTS = \
"CMakeFiles/P6.dir/P6/main.cpp.obj"

# External object files for target P6
P6_EXTERNAL_OBJECTS =

P6.exe: CMakeFiles/P6.dir/P6/main.cpp.obj
P6.exe: CMakeFiles/P6.dir/build.make
P6.exe: CMakeFiles/P6.dir/linkLibs.rsp
P6.exe: CMakeFiles/P6.dir/objects1.rsp
P6.exe: CMakeFiles/P6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Projects\VScodeCXX\ADS\SET2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable P6.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\P6.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/P6.dir/build: P6.exe
.PHONY : CMakeFiles/P6.dir/build

CMakeFiles/P6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\P6.dir\cmake_clean.cmake
.PHONY : CMakeFiles/P6.dir/clean

CMakeFiles/P6.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Projects\VScodeCXX\ADS\SET2 D:\Projects\VScodeCXX\ADS\SET2 D:\Projects\VScodeCXX\ADS\SET2\build D:\Projects\VScodeCXX\ADS\SET2\build D:\Projects\VScodeCXX\ADS\SET2\build\CMakeFiles\P6.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/P6.dir/depend

