cmake_minimum_required(VERSION 3.22)
project(my_tree C)

set(CMAKE_C_STANDARD 99)

add_executable(my_tree main.c tdbl.c tdbl.h)
