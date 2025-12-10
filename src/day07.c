#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"
const char* DAY7_PART1_ANSWER = "0";
const char* DAY7_PART2_ANSWER = "0";


void day7(const char* filename) {
    struct problem_inputs day7_lines = read_by_lines(filename);

    printf("Advent of Code, Day 07\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day7_part1(day7_lines);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day7_part2(day7_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY7_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 7, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY7_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY7_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 7, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY7_PART2_ANSWER, answer_part2);
    }


    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

char* day7_part1(struct problem_inputs p_i) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}

char* day7_part2(struct problem_inputs p_i) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}