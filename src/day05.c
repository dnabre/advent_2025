#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"

const char* DAY5_PART1_ANSWER = "17109";
const char* DAY5_PART2_ANSWER = "169347417057382";


void day5(const char* filename) {
    struct problem_inputs day5_lines = read_by_lines(filename);
;
    struct range_inputs day5_ranges = {NULL,0};
    struct problem_inputs day5_items = {NULL, 0};

    split_on_empty_range_item(day5_lines, &day5_ranges, &day5_items);

    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day5_part1(day5_lines);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day5_part2(day5_lines);

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
}


char* day5_part1(struct problem_inputs line_array) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    return answer;
}


#define DAY_05_PART_02_NUMBER_OF_BANKS 12

char* day5_part2(struct problem_inputs line_array) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    return answer;
}
