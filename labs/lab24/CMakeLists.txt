cmake_minimum_required(VERSION 3.22)
project(lab24 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab24 main.c sdbl.h sdbl.c token_queue.c token_queue.h token_stack.c token_stack.h token_tree.c token_tree.h token_struct.h sorting_station.c sorting_station.h user_interface.c user_interface.h calculation.c calculation.h error_struct.h token_tree_stack.c token_tree_stack.h token_struct.c token_vector.c token_vector.h building.c building.h)
target_link_libraries(lab24 m)
