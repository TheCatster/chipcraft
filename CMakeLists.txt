cmake_minimum_required(VERSION 3.26)
project(chipcraft C)

set(CMAKE_C_STANDARD 17)

# Locate SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Enable CTest
enable_testing()

add_library(CHIP8_LIBRARIES SHARED
        src/chip8.c
        include/chip8.h
        src/graphics.c
        include/graphics.h
        src/log.c
        include/log.h
)

target_link_libraries(CHIP8_LIBRARIES ${SDL2_LIBRARIES})

add_executable(chipcraft src/main.c
        include/main.h
)

target_link_libraries(chipcraft CHIP8_LIBRARIES)

# Test executables
add_executable(test_stack_new tests/test_stack_new.c)
add_executable(test_stack_push tests/test_stack_push.c)
add_executable(test_stack_pop tests/test_stack_pop.c)

# Link SDL and CHIP8 to the tests
target_link_libraries(test_stack_new CHIP8_LIBRARIES pthread)
target_link_libraries(test_stack_push CHIP8_LIBRARIES pthread)
target_link_libraries(test_stack_pop CHIP8_LIBRARIES pthread)

# Add tests to CTest
add_test(NAME StackNew COMMAND test_stack_new)
add_test(NAME StackPush COMMAND test_stack_push)
add_test(NAME StackPop COMMAND test_stack_pop)