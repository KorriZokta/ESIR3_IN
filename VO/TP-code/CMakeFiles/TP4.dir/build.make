# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code

# Include any dependencies generated for this target.
include CMakeFiles/TP4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TP4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP4.dir/flags.make

CMakeFiles/TP4.dir/TP4.cpp.o: CMakeFiles/TP4.dir/flags.make
CMakeFiles/TP4.dir/TP4.cpp.o: TP4.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/TP4.dir/TP4.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TP4.dir/TP4.cpp.o -c /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code/TP4.cpp

CMakeFiles/TP4.dir/TP4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP4.dir/TP4.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code/TP4.cpp > CMakeFiles/TP4.dir/TP4.cpp.i

CMakeFiles/TP4.dir/TP4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP4.dir/TP4.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code/TP4.cpp -o CMakeFiles/TP4.dir/TP4.cpp.s

CMakeFiles/TP4.dir/TP4.cpp.o.requires:
.PHONY : CMakeFiles/TP4.dir/TP4.cpp.o.requires

CMakeFiles/TP4.dir/TP4.cpp.o.provides: CMakeFiles/TP4.dir/TP4.cpp.o.requires
	$(MAKE) -f CMakeFiles/TP4.dir/build.make CMakeFiles/TP4.dir/TP4.cpp.o.provides.build
.PHONY : CMakeFiles/TP4.dir/TP4.cpp.o.provides

CMakeFiles/TP4.dir/TP4.cpp.o.provides.build: CMakeFiles/TP4.dir/TP4.cpp.o

# Object files for target TP4
TP4_OBJECTS = \
"CMakeFiles/TP4.dir/TP4.cpp.o"

# External object files for target TP4
TP4_EXTERNAL_OBJECTS =

TP4: CMakeFiles/TP4.dir/TP4.cpp.o
TP4: CMakeFiles/TP4.dir/build.make
TP4: /private/student/6/46/12010646/ESIR2IN/ViSP-build/lib64/libvisp.a
TP4: /usr/lib64/libSM.so
TP4: /usr/lib64/libICE.so
TP4: /usr/lib64/libX11.so
TP4: /usr/lib64/libXext.so
TP4: /usr/lib64/libm.so
TP4: /usr/lib64/libxml2.so
TP4: /usr/lib64/libpthread.so
TP4: /usr/lib64/libz.so
TP4: /usr/lib64/libjpeg.so
TP4: /usr/lib64/libpng.so
TP4: /usr/lib64/libz.so
TP4: /usr/lib64/libjpeg.so
TP4: /usr/lib64/libpng.so
TP4: CMakeFiles/TP4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable TP4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TP4.dir/build: TP4
.PHONY : CMakeFiles/TP4.dir/build

CMakeFiles/TP4.dir/requires: CMakeFiles/TP4.dir/TP4.cpp.o.requires
.PHONY : CMakeFiles/TP4.dir/requires

CMakeFiles/TP4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TP4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TP4.dir/clean

CMakeFiles/TP4.dir/depend:
	cd /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code /private/student/6/46/12010646/ESIR2IN/V3D/TP-code/TP-code/CMakeFiles/TP4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TP4.dir/depend

