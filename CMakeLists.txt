cmake_minimum_required(VERSION 3.29)
project(stl_3d_testing C)

set(CMAKE_C_STANDARD 11)

add_executable(stl_3d_testing main.c
        vertex.h
        binary_parser.c
)
