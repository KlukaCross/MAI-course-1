cmake_minimum_required(VERSION 3.22)
project(KP8 C)

set(CMAKE_C_STANDARD 99)

add_executable(KP8 main.c list.h list.c svint.c svint.h user_interface.h user_interface.c)
