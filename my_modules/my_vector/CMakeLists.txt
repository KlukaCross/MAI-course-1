cmake_minimum_required(VERSION 3.20)
project(my_vector C)

set(CMAKE_C_STANDARD 99)

add_executable(my_vector vdbl.c vdbl.h main.c)
