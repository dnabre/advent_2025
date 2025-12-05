#ifndef ADVENT_2025_MAIN_H
#define ADVENT_2025_MAIN_H

#include <stdint.h>
#include <stdio.h>
#define ADVENT_YEAR "2025"

struct problem_inputs{
    char** lines;
    size_t count;

};

struct int_pair{
    int64_t x;
    int64_t y;
};

struct range_inputs{
    struct int_pair* ranges;
    size_t count;
};


void free_problem_inputs(struct problem_inputs);
void free_range_inputs(struct range_inputs);
#endif //ADVENT_2025_MAIN_H
