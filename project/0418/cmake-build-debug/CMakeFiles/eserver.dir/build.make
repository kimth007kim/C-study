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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Kyungdong/Documents/C-study/project/0418

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/eserver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/eserver.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/eserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/eserver.dir/flags.make

CMakeFiles/eserver.dir/epollserver.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/epollserver.c.o: ../epollserver.c
CMakeFiles/eserver.dir/epollserver.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/eserver.dir/epollserver.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/epollserver.c.o -MF CMakeFiles/eserver.dir/epollserver.c.o.d -o CMakeFiles/eserver.dir/epollserver.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/epollserver.c

CMakeFiles/eserver.dir/epollserver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/epollserver.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/epollserver.c > CMakeFiles/eserver.dir/epollserver.c.i

CMakeFiles/eserver.dir/epollserver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/epollserver.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/epollserver.c -o CMakeFiles/eserver.dir/epollserver.c.s

CMakeFiles/eserver.dir/src/util.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/util.c.o: ../src/util.c
CMakeFiles/eserver.dir/src/util.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/eserver.dir/src/util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/util.c.o -MF CMakeFiles/eserver.dir/src/util.c.o.d -o CMakeFiles/eserver.dir/src/util.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/util.c

CMakeFiles/eserver.dir/src/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/util.c > CMakeFiles/eserver.dir/src/util.c.i

CMakeFiles/eserver.dir/src/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/util.c -o CMakeFiles/eserver.dir/src/util.c.s

CMakeFiles/eserver.dir/src/linkedlist.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/linkedlist.c.o: ../src/linkedlist.c
CMakeFiles/eserver.dir/src/linkedlist.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/eserver.dir/src/linkedlist.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/linkedlist.c.o -MF CMakeFiles/eserver.dir/src/linkedlist.c.o.d -o CMakeFiles/eserver.dir/src/linkedlist.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/linkedlist.c

CMakeFiles/eserver.dir/src/linkedlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/linkedlist.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/linkedlist.c > CMakeFiles/eserver.dir/src/linkedlist.c.i

CMakeFiles/eserver.dir/src/linkedlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/linkedlist.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/linkedlist.c -o CMakeFiles/eserver.dir/src/linkedlist.c.s

CMakeFiles/eserver.dir/src/ptr_linkedlist.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/ptr_linkedlist.c.o: ../src/ptr_linkedlist.c
CMakeFiles/eserver.dir/src/ptr_linkedlist.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/eserver.dir/src/ptr_linkedlist.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/ptr_linkedlist.c.o -MF CMakeFiles/eserver.dir/src/ptr_linkedlist.c.o.d -o CMakeFiles/eserver.dir/src/ptr_linkedlist.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/ptr_linkedlist.c

CMakeFiles/eserver.dir/src/ptr_linkedlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/ptr_linkedlist.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/ptr_linkedlist.c > CMakeFiles/eserver.dir/src/ptr_linkedlist.c.i

CMakeFiles/eserver.dir/src/ptr_linkedlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/ptr_linkedlist.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/ptr_linkedlist.c -o CMakeFiles/eserver.dir/src/ptr_linkedlist.c.s

CMakeFiles/eserver.dir/src/protocol.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/protocol.c.o: ../src/protocol.c
CMakeFiles/eserver.dir/src/protocol.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/eserver.dir/src/protocol.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/protocol.c.o -MF CMakeFiles/eserver.dir/src/protocol.c.o.d -o CMakeFiles/eserver.dir/src/protocol.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/protocol.c

CMakeFiles/eserver.dir/src/protocol.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/protocol.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/protocol.c > CMakeFiles/eserver.dir/src/protocol.c.i

CMakeFiles/eserver.dir/src/protocol.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/protocol.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/protocol.c -o CMakeFiles/eserver.dir/src/protocol.c.s

CMakeFiles/eserver.dir/src/epoll.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/epoll.c.o: ../src/epoll.c
CMakeFiles/eserver.dir/src/epoll.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/eserver.dir/src/epoll.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/epoll.c.o -MF CMakeFiles/eserver.dir/src/epoll.c.o.d -o CMakeFiles/eserver.dir/src/epoll.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/epoll.c

CMakeFiles/eserver.dir/src/epoll.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/epoll.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/epoll.c > CMakeFiles/eserver.dir/src/epoll.c.i

CMakeFiles/eserver.dir/src/epoll.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/epoll.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/epoll.c -o CMakeFiles/eserver.dir/src/epoll.c.s

CMakeFiles/eserver.dir/src/client.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/client.c.o: ../src/client.c
CMakeFiles/eserver.dir/src/client.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/eserver.dir/src/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/client.c.o -MF CMakeFiles/eserver.dir/src/client.c.o.d -o CMakeFiles/eserver.dir/src/client.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/client.c

CMakeFiles/eserver.dir/src/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/client.c > CMakeFiles/eserver.dir/src/client.c.i

CMakeFiles/eserver.dir/src/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/client.c -o CMakeFiles/eserver.dir/src/client.c.s

CMakeFiles/eserver.dir/src/server.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/server.c.o: ../src/server.c
CMakeFiles/eserver.dir/src/server.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/eserver.dir/src/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/server.c.o -MF CMakeFiles/eserver.dir/src/server.c.o.d -o CMakeFiles/eserver.dir/src/server.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/server.c

CMakeFiles/eserver.dir/src/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/server.c > CMakeFiles/eserver.dir/src/server.c.i

CMakeFiles/eserver.dir/src/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/server.c -o CMakeFiles/eserver.dir/src/server.c.s

CMakeFiles/eserver.dir/src/user.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/user.c.o: ../src/user.c
CMakeFiles/eserver.dir/src/user.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/eserver.dir/src/user.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/user.c.o -MF CMakeFiles/eserver.dir/src/user.c.o.d -o CMakeFiles/eserver.dir/src/user.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/user.c

CMakeFiles/eserver.dir/src/user.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/user.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/user.c > CMakeFiles/eserver.dir/src/user.c.i

CMakeFiles/eserver.dir/src/user.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/user.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/user.c -o CMakeFiles/eserver.dir/src/user.c.s

CMakeFiles/eserver.dir/src/network.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/network.c.o: ../src/network.c
CMakeFiles/eserver.dir/src/network.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/eserver.dir/src/network.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/network.c.o -MF CMakeFiles/eserver.dir/src/network.c.o.d -o CMakeFiles/eserver.dir/src/network.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/network.c

CMakeFiles/eserver.dir/src/network.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/network.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/network.c > CMakeFiles/eserver.dir/src/network.c.i

CMakeFiles/eserver.dir/src/network.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/network.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/network.c -o CMakeFiles/eserver.dir/src/network.c.s

CMakeFiles/eserver.dir/src/server_io.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/server_io.c.o: ../src/server_io.c
CMakeFiles/eserver.dir/src/server_io.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/eserver.dir/src/server_io.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/server_io.c.o -MF CMakeFiles/eserver.dir/src/server_io.c.o.d -o CMakeFiles/eserver.dir/src/server_io.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/server_io.c

CMakeFiles/eserver.dir/src/server_io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/server_io.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/server_io.c > CMakeFiles/eserver.dir/src/server_io.c.i

CMakeFiles/eserver.dir/src/server_io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/server_io.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/server_io.c -o CMakeFiles/eserver.dir/src/server_io.c.s

CMakeFiles/eserver.dir/src/nonblocking_io.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/nonblocking_io.c.o: ../src/nonblocking_io.c
CMakeFiles/eserver.dir/src/nonblocking_io.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/eserver.dir/src/nonblocking_io.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/nonblocking_io.c.o -MF CMakeFiles/eserver.dir/src/nonblocking_io.c.o.d -o CMakeFiles/eserver.dir/src/nonblocking_io.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/nonblocking_io.c

CMakeFiles/eserver.dir/src/nonblocking_io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/nonblocking_io.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/nonblocking_io.c > CMakeFiles/eserver.dir/src/nonblocking_io.c.i

CMakeFiles/eserver.dir/src/nonblocking_io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/nonblocking_io.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/nonblocking_io.c -o CMakeFiles/eserver.dir/src/nonblocking_io.c.s

CMakeFiles/eserver.dir/src/client_message_linkedlist.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/client_message_linkedlist.c.o: ../src/client_message_linkedlist.c
CMakeFiles/eserver.dir/src/client_message_linkedlist.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/eserver.dir/src/client_message_linkedlist.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/client_message_linkedlist.c.o -MF CMakeFiles/eserver.dir/src/client_message_linkedlist.c.o.d -o CMakeFiles/eserver.dir/src/client_message_linkedlist.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/client_message_linkedlist.c

CMakeFiles/eserver.dir/src/client_message_linkedlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/client_message_linkedlist.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/client_message_linkedlist.c > CMakeFiles/eserver.dir/src/client_message_linkedlist.c.i

CMakeFiles/eserver.dir/src/client_message_linkedlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/client_message_linkedlist.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/client_message_linkedlist.c -o CMakeFiles/eserver.dir/src/client_message_linkedlist.c.s

CMakeFiles/eserver.dir/src/client_io.c.o: CMakeFiles/eserver.dir/flags.make
CMakeFiles/eserver.dir/src/client_io.c.o: ../src/client_io.c
CMakeFiles/eserver.dir/src/client_io.c.o: CMakeFiles/eserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/eserver.dir/src/client_io.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/eserver.dir/src/client_io.c.o -MF CMakeFiles/eserver.dir/src/client_io.c.o.d -o CMakeFiles/eserver.dir/src/client_io.c.o -c /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/client_io.c

CMakeFiles/eserver.dir/src/client_io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eserver.dir/src/client_io.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/client_io.c > CMakeFiles/eserver.dir/src/client_io.c.i

CMakeFiles/eserver.dir/src/client_io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eserver.dir/src/client_io.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/src/client_io.c -o CMakeFiles/eserver.dir/src/client_io.c.s

# Object files for target eserver
eserver_OBJECTS = \
"CMakeFiles/eserver.dir/epollserver.c.o" \
"CMakeFiles/eserver.dir/src/util.c.o" \
"CMakeFiles/eserver.dir/src/linkedlist.c.o" \
"CMakeFiles/eserver.dir/src/ptr_linkedlist.c.o" \
"CMakeFiles/eserver.dir/src/protocol.c.o" \
"CMakeFiles/eserver.dir/src/epoll.c.o" \
"CMakeFiles/eserver.dir/src/client.c.o" \
"CMakeFiles/eserver.dir/src/server.c.o" \
"CMakeFiles/eserver.dir/src/user.c.o" \
"CMakeFiles/eserver.dir/src/network.c.o" \
"CMakeFiles/eserver.dir/src/server_io.c.o" \
"CMakeFiles/eserver.dir/src/nonblocking_io.c.o" \
"CMakeFiles/eserver.dir/src/client_message_linkedlist.c.o" \
"CMakeFiles/eserver.dir/src/client_io.c.o"

# External object files for target eserver
eserver_EXTERNAL_OBJECTS =

eserver: CMakeFiles/eserver.dir/epollserver.c.o
eserver: CMakeFiles/eserver.dir/src/util.c.o
eserver: CMakeFiles/eserver.dir/src/linkedlist.c.o
eserver: CMakeFiles/eserver.dir/src/ptr_linkedlist.c.o
eserver: CMakeFiles/eserver.dir/src/protocol.c.o
eserver: CMakeFiles/eserver.dir/src/epoll.c.o
eserver: CMakeFiles/eserver.dir/src/client.c.o
eserver: CMakeFiles/eserver.dir/src/server.c.o
eserver: CMakeFiles/eserver.dir/src/user.c.o
eserver: CMakeFiles/eserver.dir/src/network.c.o
eserver: CMakeFiles/eserver.dir/src/server_io.c.o
eserver: CMakeFiles/eserver.dir/src/nonblocking_io.c.o
eserver: CMakeFiles/eserver.dir/src/client_message_linkedlist.c.o
eserver: CMakeFiles/eserver.dir/src/client_io.c.o
eserver: CMakeFiles/eserver.dir/build.make
eserver: CMakeFiles/eserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking C executable eserver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/eserver.dir/build: eserver
.PHONY : CMakeFiles/eserver.dir/build

CMakeFiles/eserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/eserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/eserver.dir/clean

CMakeFiles/eserver.dir/depend:
	cd /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Kyungdong/Documents/C-study/project/0418 /mnt/c/Users/Kyungdong/Documents/C-study/project/0418 /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug /mnt/c/Users/Kyungdong/Documents/C-study/project/0418/cmake-build-debug/CMakeFiles/eserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/eserver.dir/depend

