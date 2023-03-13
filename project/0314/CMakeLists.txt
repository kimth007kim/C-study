cmake_minimum_required(VERSION 3.10)

project(my_program)

set(CMAKE_C_STANDARD 11)
#set(MODULE_EXECUTABLE server)
set(CMAKE_CXX_FLAGS "-m64 -Wall -O2 -fno-strict-aliasing -g -pthread")

#set(SOURCE_FILES
#        ${CMAKE_CURRENT_SOURCE_DIR}/epollserver.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/hashtable.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/util.c
#        )


add_executable(client epollclient.c src/util.c src/protocol.c)
add_executable(server epollserver.c  src/util.c src/linkedlist.c src/protocol.c)
add_executable(test test.c src/linkedlist.c src/util.c include/linkedlist.h)
#add_executable(${MODULE_EXECUTABLE} ${SOURCE_FILES})

install(TARGETS server client test
        DESTINATION ../../bin
        )

