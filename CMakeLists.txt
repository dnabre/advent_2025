cmake_minimum_required(VERSION 3.31)
project(advent_2025 C)

# ----- Global project settings -----
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


# ----- Source Files -----
file(GLOB DAY_SRC_FILES src/day*.c)


# ---- Target definition -----
add_executable(advent_2025
        src/main.c
        src/io.c
        src/parse.c
        ${DAY_SRC_FILES}
        src/ds.c
        src/util.c

)





# ----- Target-specific settings -----
target_include_directories(advent_2025 PRIVATE ${CMAKE_SOURCE_DIR}/include)

# --- Compiler flags by configuration ---
target_compile_options(advent_2025 PRIVATE
$<$<CONFIG:Debug>:-Wall -Wextra -Wpedantic -Wnewline-eof -Werror=implicit-function-declaration -O0 -g>
$<$<CONFIG:Release>:-Wall -Wextra -Wpedantic  -Wnewline-eof  -Werror=implicit-function-declaration -O3>
)
