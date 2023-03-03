cmake_minimum_required(VERSION 3.10)

project(my_program)

set(CMAKE_C_STANDARD 11)

add_executable(client epollclient.c my.c)
add_executable(server epollserver.c my.c)