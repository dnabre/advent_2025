#ifndef ADVENT_2025_PARSE_H
#define ADVENT_2025_PARSE_H


#include "main.h"

struct range_inputs parse_int_ranges(struct problem_inputs);

struct int_pair parse_int_range(char* str);

void split_on_empty_range_item(struct problem_inputs input_lines, struct range_inputs* out_ranges,
                               struct problem_inputs* out_items);

struct int64_vec parse_line_ints(const char* s, size_t len);

#endif //ADVENT_2025_PARSE_H
