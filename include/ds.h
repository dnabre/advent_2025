#ifndef ADVENT_2025_DS_H
#define ADVENT_2025_DS_H
#include <stddef.h>
#include <stdint.h>

struct int64_vec{
    int64_t* arr;
    size_t len;
    size_t cap;
};

void push_int64_vec(struct int64_vec* v, int64_t d);


void free_int64_vec(struct int64_vec*);
void print_int64_vec(struct int64_vec);

#endif //ADVENT_2025_DS_H