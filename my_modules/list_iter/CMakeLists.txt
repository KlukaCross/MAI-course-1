cmake_minimum_required(VERSION 3.20)
project(list_iter C)

set(CMAKE_C_STANDARD 99)

add_executable(list_iter main.c list.h list.c user_interface.h)
