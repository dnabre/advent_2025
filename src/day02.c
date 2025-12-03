#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "days.h"
#include "io.h"
#include "parse.h"


const char* DAY2_PART1_ANSWER = "23560874270";
const char* DAY2_PART2_ANSWER = "";

void day2(const char* filename) {
    struct problem_inputs day2_entries = read_full_from_csv(filename);
    struct range_inputs day2_ranges = parse_int_ranges(day2_entries);


    printf("Advent of Code, Day 02\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");

    char* answer_part1 = day2_part1(day2_ranges);
    printf("\t %s\n", answer_part1);

    // printf("\t part 2: ");
    // char* answer_part2 = day2_part2(day2_ranges);
    //
    // printf("\t %s\n", answer_part2);
    // printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY2_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 2, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY2_PART1_ANSWER, answer_part1);
    }
    // if (strcmp(answer_part2, DAY2_PART2_ANSWER) != 0)
    // {
    //     fprintf(stderr, "Day 2, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
    //             DAY2_PART2_ANSWER, answer_part2);
    // }


    if (answer_part1) { free(answer_part1); };
    // if (answer_part2) { free(answer_part2); };
}


static bool has_even_digits(int64_t n);
static int64_t check_for_twice(struct int_pair xy);


char* day2_part1(struct range_inputs i_ranges) {
    int64_t invalid_sun = 0;
    for (size_t i = 0; i < i_ranges.len; i++) {
        struct int_pair xy = i_ranges.ranges[i];
        int64_t id_sum = check_for_twice(xy);
        invalid_sun += id_sum;
    }
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, invalid_sun);
    return answer;
}





static int64_t check_for_twice(struct int_pair xy) {
    if (xy.x > xy.y) {
        printf("ERROR! invalid range: [%lld,%lld]\n", xy.x, xy.y);
        exit(-1);
    }
    int64_t sum = 0;
    char nbuffer[64];
    for (int64_t id = xy.x; id <= xy.y; id++) {
        if (!has_even_digits(id)) {
            continue;
        }
        sprintf(nbuffer, "%"PRId64, id);
        size_t len = strlen(nbuffer);
        size_t shift = len / 2;
        bool found = true;
        for (size_t s = 0; s + shift < len; s++) {
            if (nbuffer[s] != nbuffer[s + shift]) {
                found = false;
                break;
            }
        }
        if (found) {
            sum += id;
        }
    }
    return sum;
}

bool has_even_digits(int64_t n) {
    if (n < 0) n = -n;
    int count = 0;
    do {
        n /= 10;
        count++;
    }
    while (n > 0);
    return (count % 2 == 0);
}

char* day2_part2(struct range_inputs i_ranges) {

/*
 *  Repeated substring can be found by using patterns
 *   01 01 01 01 01 -> string[0] + string[1] is repeated 5 times
 *   0123 0123    -> the first four digits are repeated twice
 * Since invalid ids have to a substring repeated twice, we should
 *   started by looking at half len repeats (len/2), then (len/3),
 *   (len/4), going from largest repeated substring to shortest
 *   may not be the most efficient, but it seems the most simple
 *
 * Possilbe consider factoring the length of the string. Since
 *   the length of the repeated substring has to a fraction of
 *   the length, we can see what factors are possible for given
 *   string length. It's be crude, but there are a relatively
 *   limited number of number lengths.
 */


    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%d", 0);
    return answer;
}