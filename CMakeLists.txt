cmake_minimum_required(VERSION 4.0)
project(advent_2025 C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "-Wall -Werror -O2")

include_directories(.)

add_executable(advent_2025
        main.c
        main.h)
