cmake_minimum_required(VERSION 3.20)
project(list_stack C)

set(CMAKE_C_STANDARD 99)

add_executable(list_stack main.c sdbl.h sdbl.c)
