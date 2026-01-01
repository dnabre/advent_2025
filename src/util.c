#include "c17_strict.h"


#include <stddef.h>
#include <stdint.h>
#include "main.h"
#include "util.h"

#include <stdlib.h>

#include "ds.h"

int cmp_sizet(const void* p, const void* q){
    const size_t* a = p;
    const size_t* b = q;
    size_t left = *a;
    size_t right = *b;
    if (left < right) return -1;
    if (left > right) return 1;
    return 0;
}

int64_t calc_distance(const struct point3 a, const struct point3 b){
    const int64_t dx = a.x - b.x;
    const int64_t dy = a.y - b.y;
    const int64_t dz = a.z - b.z;
    return (dx * dx) + (dy * dy) + (dz * dz);
}


int64_t min_i64(const int64_t a, const int64_t b){
    if (a < b) {
        return a;
    }
    return b;
}

int64_t max_i64(const int64_t a, const int64_t b){
    if (a > b) {
        return a;
    }
    return b;
}


size_t min_st(const size_t a, const size_t b){
    if (a < b) {
        return a;
    }
    return b;
}

size_t max_st(const size_t a, const size_t b){
    if (a > b) {
        return a;
    }
    return b;
}

struct fstr_vec* fsplit_on_char(const char* str, const size_t len, const char ch){
    size_t count = 0;
    // count number of pieces
    size_t i = 0;
    while (i < len) {
        while (i < len && str[i] == ch) {
            i++;
        }
        if (i == len) {
            break;
        }
        count++;
        while (i < len && str[i] != ch) {
            i++;
        }
    }
    // allocte and init struct fstr_vec
    struct fstr_vec* out = malloc(sizeof(struct fstr_vec));
    init_fstr_vec_n(out, count);
    if (count == 0) {
        return out;
    }
    // find pieces and insert into out
    size_t current = 0;
    size_t k = 0;
    while (current < len && k < count) {
        while (current < len && str[current] == ch) {
            current++;
        }
        if (current == len) {
            break;
        }
        // at piece start
        const size_t start = current;
        while (current < len && str[current] != ch) {
            current++;
        }
        const size_t piece_len = current - start;
        push_fstr_vec_cn(out, &str[start], piece_len);
        k++;
    }
    return out;
}

const char* bool2str(const bool b){
    if (b) {
        return "true";
    }
    return "false";
}
