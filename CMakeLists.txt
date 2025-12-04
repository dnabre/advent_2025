cmake_minimum_required(VERSION 4.0)
project(advent_2025 C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "-Wall  -O2")


include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB DAY_SRC_FILES src/*.c)

add_executable(advent_2025
        src/main.c
        src/io.c
        src/parse.c
        ${DAY_SRC_FILES}
)