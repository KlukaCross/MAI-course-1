cmake_minimum_required(VERSION 3.20)
project(my_dynamic_vector C)

set(CMAKE_C_STANDARD 99)

add_executable(my_dynamic_vector main.c svdbl.h svdbl.c)
