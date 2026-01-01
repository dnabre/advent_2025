#ifndef ADVENT_2025_MAIN_H
#define ADVENT_2025_MAIN_H

#include <c17_strict.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#define ADVENT_YEAR "2025"


struct int_pair{
    int64_t x;
    int64_t y;
};

struct range_inputs{
    struct int_pair* ranges;
    size_t count;
};

struct problem_inputs{
    char** lines;
    size_t count;
};
struct point3{
    int64_t x;
    int64_t y;
    int64_t z;
};
struct point2{
    int64_t x;
    int64_t y;
};



struct c_grid{
    char** g;
    size_t num_rows;
    size_t num_cols;
};

struct g_pt{
    ptrdiff_t row;
    ptrdiff_t col;
};

void free_c_grid(struct c_grid);
void free_problem_inputs(struct problem_inputs);
void free_range_inputs(struct range_inputs);


#endif //ADVENT_2025_MAIN_H
