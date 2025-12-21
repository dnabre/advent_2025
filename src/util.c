


#include <stddef.h>
#include <stdint.h>
#include "main.h"
#include "util.h"

int cmp_sizet(const void* p, const void* q)
{
    const size_t* a = p;
    const size_t* b = q;
    size_t left = *a;
    size_t right = *b;
    if (left < right) return -1;
    if (left > right) return 1;
    return 0;
}

int64_t calc_distance(const struct point3  a, const struct point3 b)
{
    const int64_t dx = a.x - b.x;
    const int64_t dy = a.y - b.y;
    const int64_t dz = a.z - b.z;
    return (dx*dx) + (dy*dy) + (dz*dz);
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


