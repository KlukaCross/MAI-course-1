cmake_minimum_required(VERSION 3.20)
project(list_deque C)

set(CMAKE_C_STANDARD 99)

add_executable(list_deque main.c ddbl.h ddbl.c)
