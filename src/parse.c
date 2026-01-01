#include "c17_strict.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#include "ds.h"
#include "main.h"
#include "parse.h"


struct int_pair parse_int_range(char* str){
    char* dash = strchr(str, '-');
    if (dash) {
        *dash = '\0';
        char* right = dash + 1;
        char* left = str;
        int64_t i_l = strtoll(left, NULL, 10);
        int64_t i_r = strtoll(right, NULL, 10);

        struct int_pair result = {0, 0};
        result.x = i_l;
        result.y = i_r;
        return result;
    } else {
        printf("%s:%d, error: splitting range on dash failure on \"%s\", \n", __func__, __LINE__, str);
        exit(-1);
    }
}

struct range_inputs parse_int_ranges(struct problem_inputs p_i){
    struct range_inputs result = {0};
    result.count = p_i.count;
    struct int_pair* pair_array = malloc(p_i.count * sizeof(struct int_pair));
    for (size_t i = 0; i < p_i.count; i++) {
        char* str = p_i.lines[i];
        pair_array[i] = parse_int_range(str);
    }
    result.ranges = pair_array;

    return result;
}


void split_on_empty_range_item(struct problem_inputs input_lines, struct range_inputs* out_ranges,
                               struct problem_inputs* out_items){
    size_t split_line = SIZE_MAX;
    for (size_t i = 0; i < input_lines.count; i++) {
        if (strlen(input_lines.lines[i]) == 0) {
            split_line = i;
            break;
        }
    }

    if (split_line == SIZE_MAX) {
        printf("%s:%d, error: no empty line found while splitting input\n", __func__, __LINE__);
        exit(-1);
    }

    out_ranges->count = split_line;
    out_items->count = input_lines.count - out_ranges->count - 1;
    out_ranges->ranges = malloc(out_ranges->count * sizeof(struct int_pair));
    out_items->lines = malloc(out_items->count * sizeof(char*));
    for (size_t r = 0; r < split_line; r++) {
        out_ranges->ranges[r] = parse_int_range(input_lines.lines[r]);
    }
    size_t new_lines_idx = 0;
    for (size_t l = split_line + 1; l < input_lines.count; l++) {
        out_items->lines[new_lines_idx] = strdup(input_lines.lines[l]);
        new_lines_idx++;
    }
}


struct int64_vec parse_line_ints(const char* s, size_t len){
    struct int64_vec v = {NULL, 0, 0};


    size_t left = 0;
    size_t right = 1;

    while (right < len) {
        while (s[left] == ' ') {
            left++;
            right++;
        }
        while (('9' >= s[right]) && (s[right] >= '0')) {
            right++;
        }
        char* endptr;
        const int64_t value = strtoll(&s[left], &endptr, 10);
        push_int64_vec(&v, value);
        left = right;
        right++;
    }


    return v;
}


const size_t NUM_BUFFER_SIZE = 16;


struct point2 parse_2d_point_from_line(const char* c_line){
    char buffer[NUM_BUFFER_SIZE];
    int64_t coords[3];

    for (size_t i = 0; i < 2; i++) {
        if (i != 1) {
            char* f = strchr(c_line, ',');
            size_t len = (f - c_line);
            for (size_t c = 0; c < len; c++) {
                buffer[c] = c_line[c];
            }
            buffer[len] = '\0';
            coords[i] = strtoll(buffer, NULL, 10);
            c_line = f + 1;
        } else {
            coords[i] = strtoll(c_line, NULL, 10);
        }
    }
    const struct point2 result = {coords[0], coords[1]};
    return result;
}

struct point3 parse_3d_point_from_line(const char* c_line){
    char buffer[NUM_BUFFER_SIZE];
    int64_t coords[3];

    for (size_t i = 0; i < 3; i++) {
        if (i != 2) {
            char* f = strchr(c_line, ',');
            size_t len = (f - c_line);
            for (size_t c = 0; c < len; c++) {
                buffer[c] = c_line[c];
            }
            buffer[len] = '\0';
            coords[i] = strtoll(buffer, NULL, 10);
            c_line = f + 1;
        } else {
            coords[i] = strtoll(c_line, NULL, 10);
        }
    }
    const struct point3 result = {coords[0], coords[1], coords[2]};
    return result;
}
