cmake_minimum_required(VERSION 3.16)
project(Chip_8Emulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chip_8Emulator
        main.cpp
        Processor.cpp
        display.cpp
        tigr.c
)

# REQUIRED system libraries for Tigr (Linux)
target_link_libraries(Chip_8Emulator
        X11
        GL
        m
)
