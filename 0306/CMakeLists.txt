cmake_minimum_required(VERSION 3.10)

project(my_program)

set(CMAKE_C_STANDARD 11)

add_executable(hello hello.c my.c)
add_executable(bye bye.c my.c)

#target_include_directories(my_program PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})