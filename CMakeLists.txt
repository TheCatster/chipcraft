cmake_minimum_required(VERSION 3.26)
project(chipcraft C)

set(CMAKE_C_STANDARD 11)

add_executable(chipcraft src/main.c
        src/main.h)
