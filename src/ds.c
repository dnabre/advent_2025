#include "ds.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


//---------------- int64_vec functions start------------------
void push_int64_vec(struct int64_vec* v, int64_t d)
{
    if (v->arr == NULL) {
        v->arr = malloc(2 * sizeof(int64_t));
        v->len = 1;
        v->cap = 2;
        v->arr[0] = d;
        return;
    }

    if (v->len < v->cap) {
        v->arr[v->len] = d;
        v->len++;
        return;
    }

    if (v->len == v->cap) {
        size_t old_cap = v->cap;
        size_t new_cap = old_cap * 2;
        void* tmp = realloc(v->arr, new_cap * sizeof(int64_t));
        if (tmp == NULL) {
            printf("error, %s:%d:realloc failed (old %zu -> new %zu\n", __func__, __LINE__, old_cap, new_cap);
            free(tmp);
            v->arr = NULL;
            exit(-1);
        } else {
            v->arr = tmp;
        }
        v->cap = new_cap;
        v->arr[v->len] = d;
        v->len++;
    }
}

void free_int64_vec(struct int64_vec* v)
{
    free(v->arr);
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
}

void print_int64_vec(struct int64_vec v)
{
    if (v.arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v.len; i++) {
        printf("%"PRId64, v.arr[i]);
        if (i + 1 < v.len) {
            printf(", ");
        }
    }
    printf("]");
}


void print_int64_vec_rev(struct int64_vec v)
{
    if (v.arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = v.len - 1; i > 0; i--) {
        printf("%"PRId64, v.arr[i]);

        printf(", ");
    }
    printf("%"PRId64, v.arr[0]);
    printf("]");
}


void init_int64_vec(struct int64_vec* v)
{
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
}

//---------------- int64_vec functions end------------------


//---------------- size_vec functions start------------------
size_t push_size_vec(struct size_vec* v, const size_t d)
{
    if (v->arr == NULL) {
        v->arr = malloc(2 * sizeof(size_t));
        v->len = 1;
        v->cap = 2;
        v->arr[0] = d;
        return 0;
    }

    if (v->len < v->cap) {
        v->arr[v->len] = d;
        v->len++;
        return (v->len - 1);
    }

    if (v->len == v->cap) {
        size_t old_cap = v->cap;
        size_t new_cap = old_cap * 2;
        void* tmp = realloc(v->arr, new_cap * sizeof(size_t));
        if (tmp == NULL) {
            printf("error, %s:%d:realloc failed (old %zu -> new %zu\n", __func__, __LINE__, old_cap, new_cap);
            free(tmp);
            v->arr = NULL;
            exit(-1);
        } else {
            v->arr = tmp;
        }
        v->cap = new_cap;
        v->arr[v->len] = d;
        v->len++;
        return (v->len - 1);
    }
    return SIZE_MAX;
}

void free_size_vec(struct size_vec* v)
{
    free(v->arr);
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
}

void print_size_vec(struct size_vec v)
{
    if (v.arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v.len; i++) {
        printf("%zu", v.arr[i]);
        if (i + 1 < v.len) {
            printf(", ");
        }
    }
    printf("]");
}


void print_size_vec_rev(struct size_vec v)
{
    if (v.arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = v.len - 1; i > 0; i--) {
        printf("%zu", v.arr[i]);

        printf(", ");
    }
    printf("%zu", v.arr[0]);
    printf("]");
}


void init_size_vec(struct size_vec* v)
{
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
}

//---------------- size_vec functions end------------------
