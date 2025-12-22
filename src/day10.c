#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"
#include "util.h"
const char* DAY10_PART1_ANSWER = "0";
const char* DAY10_PART2_ANSWER = "0";


void day10(const char* filename){
    struct problem_inputs day10_lines = read_by_lines(filename);

    printf("Advent of Code, Day 10\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day10_part1(day10_lines);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day10_part2(day10_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY10_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 10, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY10_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY10_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 10, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY10_PART2_ANSWER, answer_part2);
    }


    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}
/*
 * input limits
 *  number of lights: 10
 *  number of button sets: 13
 *  number of machines : 167
 */
char* day10_part1(struct problem_inputs p_i){
    println();
    size_t b_max = 0;
    size_t bs_max = 0;
    for (size_t i = 0; i < p_i.count; i++) {
        size_t hash_count = 0;
        size_t dot_count = 0;
        size_t start_bg_count = 0;
        size_t sl = strlen(p_i.lines[i]);
        for (size_t j = 0; j < sl; j++) {
            char ch = p_i.lines[i][j];
            switch (ch) {
            case '#': hash_count++;
                break;
            case '.': dot_count++;
                break;
            case '(': start_bg_count++;
                break;
            }
        }
        b_max = max_st(b_max, hash_count + dot_count);
        bs_max = max_st(bs_max, start_bg_count);
        printf("%3zu| lights: %3zu, button sets: %3zu\t %s\n",
               i, hash_count + dot_count, start_bg_count, p_i.lines[i]
        );
    }

    printf("\nmax lights: %zu\n", b_max);
    printf("max button sets: %zu\n", bs_max);

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}

char* day10_part2(struct problem_inputs p_i){
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}
