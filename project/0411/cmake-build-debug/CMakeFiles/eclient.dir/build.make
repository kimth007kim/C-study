# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /snap/clion/234/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/234/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kim/C-study/project/0411

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kim/C-study/project/0411/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/eclient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/eclient.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/eclient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/eclient.dir/flags.make

CMakeFiles/eclient.dir/epollclient.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/epollclient.c.o: /home/kim/C-study/project/0411/epollclient.c
CMakeFiles/eclient.dir/epollclient.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/eclient.dir/epollclient.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/epollclient.c.o -MF CMakeFiles/eclient.dir/epollclient.c.o.d -o CMakeFiles/eclient.dir/epollclient.c.o -c /home/kim/C-study/project/0411/epollclient.c

CMakeFiles/eclient.dir/epollclient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/epollclient.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/epollclient.c > CMakeFiles/eclient.dir/epollclient.c.i

CMakeFiles/eclient.dir/epollclient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/epollclient.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/epollclient.c -o CMakeFiles/eclient.dir/epollclient.c.s

CMakeFiles/eclient.dir/src/util.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/src/util.c.o: /home/kim/C-study/project/0411/src/util.c
CMakeFiles/eclient.dir/src/util.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/eclient.dir/src/util.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/src/util.c.o -MF CMakeFiles/eclient.dir/src/util.c.o.d -o CMakeFiles/eclient.dir/src/util.c.o -c /home/kim/C-study/project/0411/src/util.c

CMakeFiles/eclient.dir/src/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/src/util.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/src/util.c > CMakeFiles/eclient.dir/src/util.c.i

CMakeFiles/eclient.dir/src/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/src/util.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/src/util.c -o CMakeFiles/eclient.dir/src/util.c.s

CMakeFiles/eclient.dir/src/linkedlist.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/src/linkedlist.c.o: /home/kim/C-study/project/0411/src/linkedlist.c
CMakeFiles/eclient.dir/src/linkedlist.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/eclient.dir/src/linkedlist.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/src/linkedlist.c.o -MF CMakeFiles/eclient.dir/src/linkedlist.c.o.d -o CMakeFiles/eclient.dir/src/linkedlist.c.o -c /home/kim/C-study/project/0411/src/linkedlist.c

CMakeFiles/eclient.dir/src/linkedlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/src/linkedlist.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/src/linkedlist.c > CMakeFiles/eclient.dir/src/linkedlist.c.i

CMakeFiles/eclient.dir/src/linkedlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/src/linkedlist.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/src/linkedlist.c -o CMakeFiles/eclient.dir/src/linkedlist.c.s

CMakeFiles/eclient.dir/src/ptr_linkedlist.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/src/ptr_linkedlist.c.o: /home/kim/C-study/project/0411/src/ptr_linkedlist.c
CMakeFiles/eclient.dir/src/ptr_linkedlist.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/eclient.dir/src/ptr_linkedlist.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/src/ptr_linkedlist.c.o -MF CMakeFiles/eclient.dir/src/ptr_linkedlist.c.o.d -o CMakeFiles/eclient.dir/src/ptr_linkedlist.c.o -c /home/kim/C-study/project/0411/src/ptr_linkedlist.c

CMakeFiles/eclient.dir/src/ptr_linkedlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/src/ptr_linkedlist.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/src/ptr_linkedlist.c > CMakeFiles/eclient.dir/src/ptr_linkedlist.c.i

CMakeFiles/eclient.dir/src/ptr_linkedlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/src/ptr_linkedlist.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/src/ptr_linkedlist.c -o CMakeFiles/eclient.dir/src/ptr_linkedlist.c.s

CMakeFiles/eclient.dir/src/protocol.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/src/protocol.c.o: /home/kim/C-study/project/0411/src/protocol.c
CMakeFiles/eclient.dir/src/protocol.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/eclient.dir/src/protocol.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/src/protocol.c.o -MF CMakeFiles/eclient.dir/src/protocol.c.o.d -o CMakeFiles/eclient.dir/src/protocol.c.o -c /home/kim/C-study/project/0411/src/protocol.c

CMakeFiles/eclient.dir/src/protocol.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/src/protocol.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/src/protocol.c > CMakeFiles/eclient.dir/src/protocol.c.i

CMakeFiles/eclient.dir/src/protocol.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/src/protocol.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/src/protocol.c -o CMakeFiles/eclient.dir/src/protocol.c.s

CMakeFiles/eclient.dir/src/epoll.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/src/epoll.c.o: /home/kim/C-study/project/0411/src/epoll.c
CMakeFiles/eclient.dir/src/epoll.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/eclient.dir/src/epoll.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/src/epoll.c.o -MF CMakeFiles/eclient.dir/src/epoll.c.o.d -o CMakeFiles/eclient.dir/src/epoll.c.o -c /home/kim/C-study/project/0411/src/epoll.c

CMakeFiles/eclient.dir/src/epoll.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/src/epoll.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/src/epoll.c > CMakeFiles/eclient.dir/src/epoll.c.i

CMakeFiles/eclient.dir/src/epoll.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/src/epoll.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/src/epoll.c -o CMakeFiles/eclient.dir/src/epoll.c.s

CMakeFiles/eclient.dir/src/client.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/src/client.c.o: /home/kim/C-study/project/0411/src/client.c
CMakeFiles/eclient.dir/src/client.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/eclient.dir/src/client.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/src/client.c.o -MF CMakeFiles/eclient.dir/src/client.c.o.d -o CMakeFiles/eclient.dir/src/client.c.o -c /home/kim/C-study/project/0411/src/client.c

CMakeFiles/eclient.dir/src/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/src/client.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/src/client.c > CMakeFiles/eclient.dir/src/client.c.i

CMakeFiles/eclient.dir/src/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/src/client.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/src/client.c -o CMakeFiles/eclient.dir/src/client.c.s

CMakeFiles/eclient.dir/src/server.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/src/server.c.o: /home/kim/C-study/project/0411/src/server.c
CMakeFiles/eclient.dir/src/server.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/eclient.dir/src/server.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/src/server.c.o -MF CMakeFiles/eclient.dir/src/server.c.o.d -o CMakeFiles/eclient.dir/src/server.c.o -c /home/kim/C-study/project/0411/src/server.c

CMakeFiles/eclient.dir/src/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/src/server.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/src/server.c > CMakeFiles/eclient.dir/src/server.c.i

CMakeFiles/eclient.dir/src/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/src/server.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/src/server.c -o CMakeFiles/eclient.dir/src/server.c.s

CMakeFiles/eclient.dir/src/user.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/src/user.c.o: /home/kim/C-study/project/0411/src/user.c
CMakeFiles/eclient.dir/src/user.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/eclient.dir/src/user.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/src/user.c.o -MF CMakeFiles/eclient.dir/src/user.c.o.d -o CMakeFiles/eclient.dir/src/user.c.o -c /home/kim/C-study/project/0411/src/user.c

CMakeFiles/eclient.dir/src/user.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/src/user.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/src/user.c > CMakeFiles/eclient.dir/src/user.c.i

CMakeFiles/eclient.dir/src/user.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/src/user.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/src/user.c -o CMakeFiles/eclient.dir/src/user.c.s

CMakeFiles/eclient.dir/src/network.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/src/network.c.o: /home/kim/C-study/project/0411/src/network.c
CMakeFiles/eclient.dir/src/network.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/eclient.dir/src/network.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/src/network.c.o -MF CMakeFiles/eclient.dir/src/network.c.o.d -o CMakeFiles/eclient.dir/src/network.c.o -c /home/kim/C-study/project/0411/src/network.c

CMakeFiles/eclient.dir/src/network.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/src/network.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/src/network.c > CMakeFiles/eclient.dir/src/network.c.i

CMakeFiles/eclient.dir/src/network.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/src/network.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/src/network.c -o CMakeFiles/eclient.dir/src/network.c.s

CMakeFiles/eclient.dir/src/chat.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/src/chat.c.o: /home/kim/C-study/project/0411/src/chat.c
CMakeFiles/eclient.dir/src/chat.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/eclient.dir/src/chat.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/src/chat.c.o -MF CMakeFiles/eclient.dir/src/chat.c.o.d -o CMakeFiles/eclient.dir/src/chat.c.o -c /home/kim/C-study/project/0411/src/chat.c

CMakeFiles/eclient.dir/src/chat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/src/chat.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/src/chat.c > CMakeFiles/eclient.dir/src/chat.c.i

CMakeFiles/eclient.dir/src/chat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/src/chat.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/src/chat.c -o CMakeFiles/eclient.dir/src/chat.c.s

CMakeFiles/eclient.dir/src/nonblocking_io.c.o: CMakeFiles/eclient.dir/flags.make
CMakeFiles/eclient.dir/src/nonblocking_io.c.o: /home/kim/C-study/project/0411/src/nonblocking_io.c
CMakeFiles/eclient.dir/src/nonblocking_io.c.o: CMakeFiles/eclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/eclient.dir/src/nonblocking_io.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eclient.dir/src/nonblocking_io.c.o -MF CMakeFiles/eclient.dir/src/nonblocking_io.c.o.d -o CMakeFiles/eclient.dir/src/nonblocking_io.c.o -c /home/kim/C-study/project/0411/src/nonblocking_io.c

CMakeFiles/eclient.dir/src/nonblocking_io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eclient.dir/src/nonblocking_io.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kim/C-study/project/0411/src/nonblocking_io.c > CMakeFiles/eclient.dir/src/nonblocking_io.c.i

CMakeFiles/eclient.dir/src/nonblocking_io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eclient.dir/src/nonblocking_io.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kim/C-study/project/0411/src/nonblocking_io.c -o CMakeFiles/eclient.dir/src/nonblocking_io.c.s

# Object files for target eclient
eclient_OBJECTS = \
"CMakeFiles/eclient.dir/epollclient.c.o" \
"CMakeFiles/eclient.dir/src/util.c.o" \
"CMakeFiles/eclient.dir/src/linkedlist.c.o" \
"CMakeFiles/eclient.dir/src/ptr_linkedlist.c.o" \
"CMakeFiles/eclient.dir/src/protocol.c.o" \
"CMakeFiles/eclient.dir/src/epoll.c.o" \
"CMakeFiles/eclient.dir/src/client.c.o" \
"CMakeFiles/eclient.dir/src/server.c.o" \
"CMakeFiles/eclient.dir/src/user.c.o" \
"CMakeFiles/eclient.dir/src/network.c.o" \
"CMakeFiles/eclient.dir/src/chat.c.o" \
"CMakeFiles/eclient.dir/src/nonblocking_io.c.o"

# External object files for target eclient
eclient_EXTERNAL_OBJECTS =

eclient: CMakeFiles/eclient.dir/epollclient.c.o
eclient: CMakeFiles/eclient.dir/src/util.c.o
eclient: CMakeFiles/eclient.dir/src/linkedlist.c.o
eclient: CMakeFiles/eclient.dir/src/ptr_linkedlist.c.o
eclient: CMakeFiles/eclient.dir/src/protocol.c.o
eclient: CMakeFiles/eclient.dir/src/epoll.c.o
eclient: CMakeFiles/eclient.dir/src/client.c.o
eclient: CMakeFiles/eclient.dir/src/server.c.o
eclient: CMakeFiles/eclient.dir/src/user.c.o
eclient: CMakeFiles/eclient.dir/src/network.c.o
eclient: CMakeFiles/eclient.dir/src/chat.c.o
eclient: CMakeFiles/eclient.dir/src/nonblocking_io.c.o
eclient: CMakeFiles/eclient.dir/build.make
eclient: CMakeFiles/eclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking C executable eclient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/eclient.dir/build: eclient
.PHONY : CMakeFiles/eclient.dir/build

CMakeFiles/eclient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/eclient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/eclient.dir/clean

CMakeFiles/eclient.dir/depend:
	cd /home/kim/C-study/project/0411/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kim/C-study/project/0411 /home/kim/C-study/project/0411 /home/kim/C-study/project/0411/cmake-build-debug /home/kim/C-study/project/0411/cmake-build-debug /home/kim/C-study/project/0411/cmake-build-debug/CMakeFiles/eclient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/eclient.dir/depend

