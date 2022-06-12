cmake_minimum_required(VERSION 3.20)
project(file_queue C)

set(CMAKE_C_STANDARD 99)

add_executable(file_queue main.c qdbl.c qdbl.h)
