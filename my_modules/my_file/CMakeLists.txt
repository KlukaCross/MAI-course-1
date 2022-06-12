cmake_minimum_required(VERSION 3.22)
project(my_file C)

set(CMAKE_C_STANDARD 99)

add_executable(my_file main.c file_int.c file_int.h)
