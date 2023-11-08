cmake_minimum_required(VERSION 3.26)
project(chipcraft C)

set(CMAKE_C_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(chipcraft src/main.c
        include/main.h
        src/chip8.c
        include/chip8.h
        src/graphics.c
        include/graphics.h
        src/log.c
        include/log.h
)

target_link_libraries(chipcraft ${SDL2_LIBRARIES})