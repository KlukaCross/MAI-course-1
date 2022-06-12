cmake_minimum_required(VERSION 3.20)
project(my_static_stack C)

set(CMAKE_C_STANDARD 99)

add_executable(my_static_stack main.c sdbl.c sdbl.h)
