cmake_minimum_required(VERSION 3.20)
project(my_static_deque C)

set(CMAKE_C_STANDARD 99)

add_executable(my_static_deque main.c ddbl.h ddbl.cpp ddbl.c)
