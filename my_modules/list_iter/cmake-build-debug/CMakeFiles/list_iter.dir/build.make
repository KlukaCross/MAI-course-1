# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /snap/clion/190/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/190/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/list_iter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/list_iter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/list_iter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/list_iter.dir/flags.make

CMakeFiles/list_iter.dir/main.c.o: CMakeFiles/list_iter.dir/flags.make
CMakeFiles/list_iter.dir/main.c.o: ../main.c
CMakeFiles/list_iter.dir/main.c.o: CMakeFiles/list_iter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/list_iter.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/list_iter.dir/main.c.o -MF CMakeFiles/list_iter.dir/main.c.o.d -o CMakeFiles/list_iter.dir/main.c.o -c /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/main.c

CMakeFiles/list_iter.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/list_iter.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/main.c > CMakeFiles/list_iter.dir/main.c.i

CMakeFiles/list_iter.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/list_iter.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/main.c -o CMakeFiles/list_iter.dir/main.c.s

CMakeFiles/list_iter.dir/list.c.o: CMakeFiles/list_iter.dir/flags.make
CMakeFiles/list_iter.dir/list.c.o: ../list.c
CMakeFiles/list_iter.dir/list.c.o: CMakeFiles/list_iter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/list_iter.dir/list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/list_iter.dir/list.c.o -MF CMakeFiles/list_iter.dir/list.c.o.d -o CMakeFiles/list_iter.dir/list.c.o -c /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/list.c

CMakeFiles/list_iter.dir/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/list_iter.dir/list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/list.c > CMakeFiles/list_iter.dir/list.c.i

CMakeFiles/list_iter.dir/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/list_iter.dir/list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/list.c -o CMakeFiles/list_iter.dir/list.c.s

# Object files for target list_iter
list_iter_OBJECTS = \
"CMakeFiles/list_iter.dir/main.c.o" \
"CMakeFiles/list_iter.dir/list.c.o"

# External object files for target list_iter
list_iter_EXTERNAL_OBJECTS =

list_iter: CMakeFiles/list_iter.dir/main.c.o
list_iter: CMakeFiles/list_iter.dir/list.c.o
list_iter: CMakeFiles/list_iter.dir/build.make
list_iter: CMakeFiles/list_iter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable list_iter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/list_iter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/list_iter.dir/build: list_iter
.PHONY : CMakeFiles/list_iter.dir/build

CMakeFiles/list_iter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/list_iter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/list_iter.dir/clean

CMakeFiles/list_iter.dir/depend:
	cd /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/cmake-build-debug /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/cmake-build-debug /home/aprold/Documents/GitHub/MAIwork/1course/my_modules/list_iter/cmake-build-debug/CMakeFiles/list_iter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/list_iter.dir/depend

