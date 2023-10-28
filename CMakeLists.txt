cmake_minimum_required(VERSION 3.26)
project(chipcraft C)

set(CMAKE_C_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(chipcraft src/main.c
        src/main.h
        src/chip8.c
        src/chip8.h
        src/graphics.c
        src/graphics.h
)

target_link_libraries(chipcraft ${SDL2_LIBRARIES})