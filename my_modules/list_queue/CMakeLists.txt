cmake_minimum_required(VERSION 3.20)
project(list_queue C)

set(CMAKE_C_STANDARD 99)

add_executable(list_queue main.c qdbl.h qdbl.c)
