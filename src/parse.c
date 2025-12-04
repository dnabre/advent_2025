#include "main.h"
#include "parse.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct range_inputs parse_int_ranges(struct problem_inputs p_i) {
    struct range_inputs result = {0};
    result.len = p_i.len;
    struct int_pair* pair_array = malloc(p_i.len * sizeof(struct int_pair));
    for (size_t i = 0; i < p_i.len; i++) {
        char* str = p_i.inputs[i];
        char* dash = strchr(str, '-');
        if (dash) {
            *dash = '\0';
            char* right = dash + 1;
            char* left = str;
            int64_t i_l = strtoll(left, NULL, 10);
            int64_t i_r = strtoll(right, NULL, 10);

            struct int_pair xy;
            xy.x = i_l;
            xy.y = i_r;
            pair_array[i] = xy;
        }
        else {
            fprintf(stderr, "Parse error of int range: %s\n", str);
        }
    }
    result.ranges = pair_array;

    return result;
}
