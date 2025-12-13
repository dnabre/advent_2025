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
void print_int64_vec_rev(struct int64_vec);
void init_int64_vec(struct int64_vec*);
typedef struct{
    char* s;
    size_t len;
} d_string;

void free_dstring(const d_string*);


struct dstr_vec{
    d_string* arr;
    size_t len;
    size_t cap;
};

void push_dstr_vec(struct dstr_vec* v, d_string d);
void free_dstr_vec(struct dstr_vec*);
void print_dstr_vec(struct dstr_vec);
void init_dstr_vec(struct dstr_vec*);


#endif //ADVENT_2025_DS_H
