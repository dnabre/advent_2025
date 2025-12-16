#ifndef ADVENT_2025_DS_H
#define ADVENT_2025_DS_H
#include <stdbool.h>
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
void print_int64_vec_rev(struct int64_vec);
void init_int64_vec(struct int64_vec*);


struct size_vec{
    size_t* arr;
    size_t len;
    size_t cap;
};

size_t push_size_vec(struct size_vec* v, size_t d);
void free_size_vec(struct size_vec*);
void print_size_vec(struct size_vec);
void print_size_vec_rev(struct size_vec);
void init_size_vec(struct size_vec*);
void init_size_vec_with_size(struct size_vec*, size_t init_size);

// static bool grow_size_vec(struct size_vec* v, const size_t ptrsize, size_t* curcount);

static inline int  size_t_compare(const void *p1, const void *p2)
{
    size_t left = *(const int *)p1;
    size_t right = *(const int *)p2;

    return ((left > right) - (left < right));
}

static inline int  size_t_compare_r(const void *p1, const void *p2)
{
    size_t left = *(const int *)p2;
    size_t right = *(const int *)p1;

    return ((left > right) - (left < right));
}

#endif //ADVENT_2025_DS_H
