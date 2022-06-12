cmake_minimum_required(VERSION 3.20)
project(my_dynamic_queue C)

set(CMAKE_C_STANDARD 99)

add_executable(my_dynamic_queue qdbl.c qdbl.h)
