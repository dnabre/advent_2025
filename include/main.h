#ifndef ADVENT_2025_MAIN_H
#define ADVENT_2025_MAIN_H

#include <stdint.h>
#include <stdio.h>
#define ADVENT_YEAR "2025"

struct problem_inputs{
    size_t len;
    char** inputs;
};

struct int_pair{
    int64_t x;
    int64_t y;
};

struct range_inputs{
    struct int_pair* ranges;
    size_t len;
};
#endif //ADVENT_2025_MAIN_H
