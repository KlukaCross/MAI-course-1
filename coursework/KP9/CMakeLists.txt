cmake_minimum_required(VERSION 3.22)
project(KP9 C)

set(CMAKE_C_STANDARD 99)

add_executable(KP9 main.c item.h vitem.h vitem.c user_interface.c user_interface.h item.c sort_hoar.c sort_hoar.h)
target_link_libraries(KP9 -lquadmath)
