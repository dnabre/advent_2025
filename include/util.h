#ifndef ADVENT_2025_UTIL_H
#define ADVENT_2025_UTIL_H
int cmp_sizet(const void* p, const void* q);
int64_t calc_distance(const struct point3  a, const struct point3 b);

int64_t min_i64(const int64_t a, const int64_t b);
int64_t max_i64(const int64_t a, const int64_t b);


size_t min_st(const size_t a, const size_t b);
size_t max_st(const size_t a, const size_t b);


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

// return fstr_vec and the fstring within are newly allocated
struct fstr_vec* fsplit_on_char(const char* str, const size_t len, const char ch);
#endif //ADVENT_2025_UTIL_H