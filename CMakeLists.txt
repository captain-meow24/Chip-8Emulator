cmake_minimum_required(VERSION 3.31)
project(Chip_8Emulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Chip_8Emulator main.cpp
        Processor.cpp
        Processor.h
        display.cpp
        display.h)

