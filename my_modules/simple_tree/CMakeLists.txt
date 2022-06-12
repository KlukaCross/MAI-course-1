cmake_minimum_required(VERSION 3.22)
project(simple_stree C)

set(CMAKE_C_STANDARD 99)

add_executable(simple_stree main.c stree_int.h stree_int.c)
