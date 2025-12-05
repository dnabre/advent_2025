#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"

const char* DAY4_PART1_ANSWER = "17109";
const char* DAY4_PART2_ANSWER = "169347417057382";


void day4(const char* filename) {
    struct problem_inputs day4_lines = read_by_lines(filename);



    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day4_part1(day4_lines);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day4_part2(day4_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY4_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 4, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
            DAY4_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY4_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 4, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
            DAY4_PART2_ANSWER, answer_part2);
    }

    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}


char* day4_part1(struct problem_inputs line_array) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    return answer;
}


#define DAY_04_PART_02_NUMBER_OF_BANKS 12

char* day4_part2(struct problem_inputs line_array) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    return answer;
}
