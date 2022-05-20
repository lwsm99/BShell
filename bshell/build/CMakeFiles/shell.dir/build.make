# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/student/Desktop/BS/HU/bshell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/student/Desktop/BS/HU/bshell/build

# Include any dependencies generated for this target.
include CMakeFiles/shell.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shell.dir/flags.make

tokenparser.c: ../src/tokenparser.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[BISON][BSParser] Building parser with bison 3.3.2"
	cd /home/student/Desktop/BS/HU/bshell && /usr/bin/bison --defines=/home/student/Desktop/BS/HU/bshell/build/tokenparser.h -o /home/student/Desktop/BS/HU/bshell/build/tokenparser.c src/tokenparser.y

tokenparser.h: tokenparser.c
	@$(CMAKE_COMMAND) -E touch_nocreate tokenparser.h

tokenscanner.c: ../src/tokenscanner.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "[FLEX][BSScanner] Building scanner with flex 2.6.4"
	cd /home/student/Desktop/BS/HU/bshell && /usr/bin/flex -o/home/student/Desktop/BS/HU/bshell/build/tokenscanner.c src/tokenscanner.l

CMakeFiles/shell.dir/src/command.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/command.c.o: ../src/command.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/shell.dir/src/command.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/src/command.c.o   -c /home/student/Desktop/BS/HU/bshell/src/command.c

CMakeFiles/shell.dir/src/command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/command.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/student/Desktop/BS/HU/bshell/src/command.c > CMakeFiles/shell.dir/src/command.c.i

CMakeFiles/shell.dir/src/command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/command.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/student/Desktop/BS/HU/bshell/src/command.c -o CMakeFiles/shell.dir/src/command.c.s

CMakeFiles/shell.dir/src/helper.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/helper.c.o: ../src/helper.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/shell.dir/src/helper.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/src/helper.c.o   -c /home/student/Desktop/BS/HU/bshell/src/helper.c

CMakeFiles/shell.dir/src/helper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/helper.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/student/Desktop/BS/HU/bshell/src/helper.c > CMakeFiles/shell.dir/src/helper.c.i

CMakeFiles/shell.dir/src/helper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/helper.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/student/Desktop/BS/HU/bshell/src/helper.c -o CMakeFiles/shell.dir/src/helper.c.s

CMakeFiles/shell.dir/src/list.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/list.c.o: ../src/list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/shell.dir/src/list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/src/list.c.o   -c /home/student/Desktop/BS/HU/bshell/src/list.c

CMakeFiles/shell.dir/src/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/student/Desktop/BS/HU/bshell/src/list.c > CMakeFiles/shell.dir/src/list.c.i

CMakeFiles/shell.dir/src/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/student/Desktop/BS/HU/bshell/src/list.c -o CMakeFiles/shell.dir/src/list.c.s

CMakeFiles/shell.dir/src/execute.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/execute.c.o: ../src/execute.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/shell.dir/src/execute.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/src/execute.c.o   -c /home/student/Desktop/BS/HU/bshell/src/execute.c

CMakeFiles/shell.dir/src/execute.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/execute.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/student/Desktop/BS/HU/bshell/src/execute.c > CMakeFiles/shell.dir/src/execute.c.i

CMakeFiles/shell.dir/src/execute.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/execute.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/student/Desktop/BS/HU/bshell/src/execute.c -o CMakeFiles/shell.dir/src/execute.c.s

CMakeFiles/shell.dir/src/statuslist.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/statuslist.c.o: ../src/statuslist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/shell.dir/src/statuslist.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/src/statuslist.c.o   -c /home/student/Desktop/BS/HU/bshell/src/statuslist.c

CMakeFiles/shell.dir/src/statuslist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/statuslist.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/student/Desktop/BS/HU/bshell/src/statuslist.c > CMakeFiles/shell.dir/src/statuslist.c.i

CMakeFiles/shell.dir/src/statuslist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/statuslist.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/student/Desktop/BS/HU/bshell/src/statuslist.c -o CMakeFiles/shell.dir/src/statuslist.c.s

CMakeFiles/shell.dir/src/shell.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/shell.c.o: ../src/shell.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/shell.dir/src/shell.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/src/shell.c.o   -c /home/student/Desktop/BS/HU/bshell/src/shell.c

CMakeFiles/shell.dir/src/shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/shell.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/student/Desktop/BS/HU/bshell/src/shell.c > CMakeFiles/shell.dir/src/shell.c.i

CMakeFiles/shell.dir/src/shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/shell.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/student/Desktop/BS/HU/bshell/src/shell.c -o CMakeFiles/shell.dir/src/shell.c.s

CMakeFiles/shell.dir/src/readlineparsing.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/readlineparsing.c.o: ../src/readlineparsing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/shell.dir/src/readlineparsing.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/src/readlineparsing.c.o   -c /home/student/Desktop/BS/HU/bshell/src/readlineparsing.c

CMakeFiles/shell.dir/src/readlineparsing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/readlineparsing.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/student/Desktop/BS/HU/bshell/src/readlineparsing.c > CMakeFiles/shell.dir/src/readlineparsing.c.i

CMakeFiles/shell.dir/src/readlineparsing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/readlineparsing.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/student/Desktop/BS/HU/bshell/src/readlineparsing.c -o CMakeFiles/shell.dir/src/readlineparsing.c.s

CMakeFiles/shell.dir/src/stringbuffer.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/stringbuffer.c.o: ../src/stringbuffer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/shell.dir/src/stringbuffer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/src/stringbuffer.c.o   -c /home/student/Desktop/BS/HU/bshell/src/stringbuffer.c

CMakeFiles/shell.dir/src/stringbuffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/stringbuffer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/student/Desktop/BS/HU/bshell/src/stringbuffer.c > CMakeFiles/shell.dir/src/stringbuffer.c.i

CMakeFiles/shell.dir/src/stringbuffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/stringbuffer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/student/Desktop/BS/HU/bshell/src/stringbuffer.c -o CMakeFiles/shell.dir/src/stringbuffer.c.s

CMakeFiles/shell.dir/tokenparser.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/tokenparser.c.o: tokenparser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/shell.dir/tokenparser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/tokenparser.c.o   -c /home/student/Desktop/BS/HU/bshell/build/tokenparser.c

CMakeFiles/shell.dir/tokenparser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/tokenparser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/student/Desktop/BS/HU/bshell/build/tokenparser.c > CMakeFiles/shell.dir/tokenparser.c.i

CMakeFiles/shell.dir/tokenparser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/tokenparser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/student/Desktop/BS/HU/bshell/build/tokenparser.c -o CMakeFiles/shell.dir/tokenparser.c.s

CMakeFiles/shell.dir/tokenscanner.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/tokenscanner.c.o: tokenscanner.c
CMakeFiles/shell.dir/tokenscanner.c.o: tokenparser.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/shell.dir/tokenscanner.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/tokenscanner.c.o   -c /home/student/Desktop/BS/HU/bshell/build/tokenscanner.c

CMakeFiles/shell.dir/tokenscanner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/tokenscanner.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/student/Desktop/BS/HU/bshell/build/tokenscanner.c > CMakeFiles/shell.dir/tokenscanner.c.i

CMakeFiles/shell.dir/tokenscanner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/tokenscanner.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/student/Desktop/BS/HU/bshell/build/tokenscanner.c -o CMakeFiles/shell.dir/tokenscanner.c.s

# Object files for target shell
shell_OBJECTS = \
"CMakeFiles/shell.dir/src/command.c.o" \
"CMakeFiles/shell.dir/src/helper.c.o" \
"CMakeFiles/shell.dir/src/list.c.o" \
"CMakeFiles/shell.dir/src/execute.c.o" \
"CMakeFiles/shell.dir/src/statuslist.c.o" \
"CMakeFiles/shell.dir/src/shell.c.o" \
"CMakeFiles/shell.dir/src/readlineparsing.c.o" \
"CMakeFiles/shell.dir/src/stringbuffer.c.o" \
"CMakeFiles/shell.dir/tokenparser.c.o" \
"CMakeFiles/shell.dir/tokenscanner.c.o"

# External object files for target shell
shell_EXTERNAL_OBJECTS =

shell: CMakeFiles/shell.dir/src/command.c.o
shell: CMakeFiles/shell.dir/src/helper.c.o
shell: CMakeFiles/shell.dir/src/list.c.o
shell: CMakeFiles/shell.dir/src/execute.c.o
shell: CMakeFiles/shell.dir/src/statuslist.c.o
shell: CMakeFiles/shell.dir/src/shell.c.o
shell: CMakeFiles/shell.dir/src/readlineparsing.c.o
shell: CMakeFiles/shell.dir/src/stringbuffer.c.o
shell: CMakeFiles/shell.dir/tokenparser.c.o
shell: CMakeFiles/shell.dir/tokenscanner.c.o
shell: CMakeFiles/shell.dir/build.make
shell: /usr/lib/x86_64-linux-gnu/libfl.so
shell: /usr/lib/x86_64-linux-gnu/libreadline.so
shell: CMakeFiles/shell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/student/Desktop/BS/HU/bshell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking C executable shell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shell.dir/build: shell

.PHONY : CMakeFiles/shell.dir/build

CMakeFiles/shell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shell.dir/clean

CMakeFiles/shell.dir/depend: tokenparser.c
CMakeFiles/shell.dir/depend: tokenparser.h
CMakeFiles/shell.dir/depend: tokenscanner.c
	cd /home/student/Desktop/BS/HU/bshell/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/student/Desktop/BS/HU/bshell /home/student/Desktop/BS/HU/bshell /home/student/Desktop/BS/HU/bshell/build /home/student/Desktop/BS/HU/bshell/build /home/student/Desktop/BS/HU/bshell/build/CMakeFiles/shell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shell.dir/depend

