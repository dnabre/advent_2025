#include "c17_strict.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "days.h"
#include "io.h"
#include "parse.h"


const char* DAY2_PART1_ANSWER = "23560874270";
const char* DAY2_PART2_ANSWER = "44143124633";

void day2(const char* filename){
    struct problem_inputs day2_entries = read_full_from_csv(filename);
    struct range_inputs day2_ranges = parse_int_ranges(day2_entries);


    printf("Advent of Code, Day 02\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");

    char* answer_part1 = day2_part1(day2_ranges);
    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day2_part2(day2_ranges);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY2_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 2, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY2_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY2_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 2, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY2_PART2_ANSWER, answer_part2);
    }


    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}


static bool is_repeated_twice(const char* str, size_t n);
static bool is_repeated_substring(const char* str, size_t n);


char* day2_part1(struct range_inputs i_ranges){
    int64_t invalid_sum = 0;
    char nbuffer[64];
    for (size_t i = 0; i < i_ranges.count; i++) {
        struct int_pair xy = i_ranges.ranges[i];;
        for (int64_t id = xy.x; id <= xy.y; id++) {
            size_t len = sprintf(nbuffer, "%"PRId64, id);
            if (is_repeated_twice(nbuffer, len)) {
                invalid_sum += id;
            }
        }
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, invalid_sum);
    return answer;
}

char* day2_part2(struct range_inputs i_ranges){
    int64_t invalid_sum = 0;
    char nbuffer[64];
    for (size_t i = 0; i < i_ranges.count; i++) {
        struct int_pair xy = i_ranges.ranges[i];;
        for (int64_t id = xy.x; id <= xy.y; id++) {
            size_t len = sprintf(nbuffer, "%"PRId64, id);
            if (is_repeated_substring(nbuffer, len)) {
                invalid_sum += id;
            }
        }
    }


    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, invalid_sum);
    return answer;
}

static bool is_repeated_twice(const char* str, size_t n){
    if (n % 2 != 0) {
        return false;
    }
    bool ok = true;
    size_t step = n / 2;
    for (size_t i = 0; i < (n / 2); i++) {
        if (str[i] != str[i + step]) {
            ok = false;
            break;
        }
    }
    if (ok) return true;
    return false;
}

static bool is_repeated_substring(const char* str, size_t n){
    for (size_t d = 1; d <= n / 2; d++) {
        if (n % d != 0) {
            continue;
        }
        bool ok = true;
        for (size_t i = d; i < n; i++) {
            if (str[i] != str[i % d]) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
    }
    return false;
}
