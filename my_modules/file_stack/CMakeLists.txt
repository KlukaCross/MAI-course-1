cmake_minimum_required(VERSION 3.20)
project(file_stack C)

set(CMAKE_C_STANDARD 99)

add_executable(file_stack main.c sdbl.h sdbl.c)
