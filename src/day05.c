#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"
#include "parse.h"

const char* DAY5_PART1_ANSWER = "635";
const char* DAY5_PART2_ANSWER = "369761800782619";


static int int_pair_compare(const void* p1, const void* p2);

static inline int64_t max_int(int64_t a, int64_t b) {
    return a > b ? a : b;
}

void day5(const char* filename) {
    struct problem_inputs day5_lines = read_by_lines(filename);
    struct range_inputs day5_ranges = {NULL, 0};
    struct problem_inputs day5_items = {NULL, 0};

    split_on_empty_range_item(day5_lines, &day5_ranges, &day5_items);

    printf("Advent of Code, Day 05\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day5_part1(day5_ranges, day5_items);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day5_part2(day5_ranges, day5_items);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY5_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 5, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY5_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY5_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 5, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY5_PART2_ANSWER, answer_part2);
    }

    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };

    free_problem_inputs(day5_lines);
    free_range_inputs(day5_ranges);
    free_problem_inputs(day5_items);
}

char* day5_part1(struct range_inputs day5_ranges, struct problem_inputs day5_items) {
    size_t fresh_count = 0;
    for (size_t i = 0; i < day5_items.count; i++) {
        int64_t id = strtoll(day5_items.lines[i],NULL, 10);
        bool food_fresh = false;
        for (size_t j = 0; j < day5_ranges.count; j++) {
            int64_t left = day5_ranges.ranges[j].x;
            int64_t right = day5_ranges.ranges[j].y;
            if ((left <= id) && (id <= right)) {
                food_fresh = true;
                break;
            }
        }
        if (food_fresh) {
            fresh_count++;
        }
    }


    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, fresh_count);
    return answer;
}


char* day5_part2(struct range_inputs day5_ranges, struct problem_inputs day5_items) {
    struct int_pair* range_array = day5_ranges.ranges;
    printf("pre-sort:\n\t");
    for (size_t i = 0; i < day5_ranges.count; i++) {
        print_int_pair_range(range_array[i]);
        printf("\n\t");
    }


    qsort(range_array, day5_ranges.count, sizeof(struct int_pair), int_pair_compare);

    printf("\n\npostsort:\n\t");
    for (size_t i = 0; i < day5_ranges.count; i++) {
        print_int_pair_range(range_array[i]);
        printf("\n\t");
    }
    int64_t in_range_items = 0;
    struct int_pair merged = range_array[0];

    for (size_t r_idx = 1; r_idx < day5_ranges.count; r_idx++) {
        struct int_pair current_range = range_array[r_idx];;
        if (current_range.x <= merged.y) {
            merged.y = max_int(merged.y, current_range.y);
        } else {
            printf("no more to merge into ");
            print_int_pair_range(merged);
            printf(" talling %zu items into %zu -> ", merged.y - merged.x + 1, in_range_items);
            in_range_items += merged.y - merged.x + 1;

            printf("%zu\n", in_range_items);
            merged = current_range;
        }
    }
    printf("adding last merge: ");
    print_int_pair_range(merged);
    printf(" talling %zu items into %zu -> ", merged.y - merged.x + 1, in_range_items);
    in_range_items += merged.y - merged.x + 1;


    println();
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, in_range_items);
    return answer;
}


static int int_pair_compare(const void* p1, const void* p2) {
    int64_t left_x, left_y, right_x, right_y;

    left_x = ((struct int_pair*)p1)->x;
    left_y = ((struct int_pair*)p1)->y;

    right_x = ((struct int_pair*)p2)->x;
    right_y = ((struct int_pair*)p2)->y;

    int x_compare = ((left_x > right_x) - (left_x < right_x));
    if (x_compare == 0) {
        int y_compare = ((left_y > right_y) - (left_y < right_y));
        return y_compare;
    }
    else {
        return x_compare;
    }
}
