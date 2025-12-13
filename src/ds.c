
#include "ds.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>





void push_int64_vec(struct int64_vec* v, int64_t d) {

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
        void *tmp =realloc(v->arr, new_cap * sizeof(int64_t));
        if (tmp == NULL) {
            printf("error, %s:%d:realloc failed (old %zu -> new %zu\n",__func__, __LINE__, old_cap, new_cap );
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

void free_int64_vec(struct int64_vec* v) {
    free(v->arr);
    v->len=0;
    v->cap=0;
}

void print_int64_vec(struct int64_vec v) {

    if (v.arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v.len; i++) {
        printf("%"PRId64, v.arr[i]); // %zu is the correct specifier for size_t
        if (i + 1 < v.len) {
            printf(", ");
        }
    }
    printf("]");
}