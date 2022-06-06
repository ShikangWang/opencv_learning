# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wsk/codes/cv_learning/filter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wsk/codes/cv_learning/filter/build

# Include any dependencies generated for this target.
include CMakeFiles/filter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/filter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/filter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/filter.dir/flags.make

CMakeFiles/filter.dir/filter.o: CMakeFiles/filter.dir/flags.make
CMakeFiles/filter.dir/filter.o: ../filter.cpp
CMakeFiles/filter.dir/filter.o: CMakeFiles/filter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wsk/codes/cv_learning/filter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/filter.dir/filter.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/filter.dir/filter.o -MF CMakeFiles/filter.dir/filter.o.d -o CMakeFiles/filter.dir/filter.o -c /home/wsk/codes/cv_learning/filter/filter.cpp

CMakeFiles/filter.dir/filter.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/filter.dir/filter.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wsk/codes/cv_learning/filter/filter.cpp > CMakeFiles/filter.dir/filter.i

CMakeFiles/filter.dir/filter.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/filter.dir/filter.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wsk/codes/cv_learning/filter/filter.cpp -o CMakeFiles/filter.dir/filter.s

# Object files for target filter
filter_OBJECTS = \
"CMakeFiles/filter.dir/filter.o"

# External object files for target filter
filter_EXTERNAL_OBJECTS =

filter: CMakeFiles/filter.dir/filter.o
filter: CMakeFiles/filter.dir/build.make
filter: /usr/local/lib/libopencv_gapi.so.4.5.5
filter: /usr/local/lib/libopencv_highgui.so.4.5.5
filter: /usr/local/lib/libopencv_ml.so.4.5.5
filter: /usr/local/lib/libopencv_objdetect.so.4.5.5
filter: /usr/local/lib/libopencv_photo.so.4.5.5
filter: /usr/local/lib/libopencv_stitching.so.4.5.5
filter: /usr/local/lib/libopencv_video.so.4.5.5
filter: /usr/local/lib/libopencv_videoio.so.4.5.5
filter: /usr/local/lib/libopencv_imgcodecs.so.4.5.5
filter: /usr/local/lib/libopencv_dnn.so.4.5.5
filter: /usr/local/lib/libopencv_calib3d.so.4.5.5
filter: /usr/local/lib/libopencv_features2d.so.4.5.5
filter: /usr/local/lib/libopencv_flann.so.4.5.5
filter: /usr/local/lib/libopencv_imgproc.so.4.5.5
filter: /usr/local/lib/libopencv_core.so.4.5.5
filter: CMakeFiles/filter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wsk/codes/cv_learning/filter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable filter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/filter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/filter.dir/build: filter
.PHONY : CMakeFiles/filter.dir/build

CMakeFiles/filter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/filter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/filter.dir/clean

CMakeFiles/filter.dir/depend:
	cd /home/wsk/codes/cv_learning/filter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wsk/codes/cv_learning/filter /home/wsk/codes/cv_learning/filter /home/wsk/codes/cv_learning/filter/build /home/wsk/codes/cv_learning/filter/build /home/wsk/codes/cv_learning/filter/build/CMakeFiles/filter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/filter.dir/depend

