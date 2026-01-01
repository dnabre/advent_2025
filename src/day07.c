#include "c17_strict.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"
const char* DAY7_PART1_ANSWER = "1656";
const char* DAY7_PART2_ANSWER = "76624086587804";


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
    const size_t width = strlen(p_i.lines[0]);
    const size_t height = p_i.count;
    char** grid = p_i.lines;
    int64_t beams[width];
    for (size_t i=0; i < width; i++) {
        beams[i] = 0;
    }
    int64_t split_count=0;
    for (size_t h=0; h < height; h++) {
       for (size_t w=0; w < width; w++) {
            char ch = grid[h][w];
            if (ch == 'S') {
                beams[w] = 1;
            }
            if (ch == '^') {
                if (beams[w] == 1) {
                    split_count++;
                    beams[w] = 0;
                    beams[w-1] = 1;
                    beams[w+1] = 1;
                }
            }
        }
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, split_count);
    return answer;
}

char* day7_part2(struct problem_inputs p_i) {
    const size_t width = strlen(p_i.lines[0]);
    const size_t height = p_i.count;
    char** grid = p_i.lines;
    int64_t beams[width];
    for (size_t i=0; i < width; i++) {
        beams[i] = 0;
    }

    for (size_t h=0; h < height; h++) {
        for (size_t w=0; w < width; w++) {
            char ch = grid[h][w];
            if (ch == 'S') {
                beams[w]=1;
            }
            if (ch == '^') {
                if (beams[w] > 0) {
                    const int64_t last = beams[w];
                    beams[w] = 0;
                    beams[w-1]  += last;
                    beams[w+1] += last;

                }
            }
        }
    }
    int64_t tach_count =0;
    for (size_t w=0; w < width; w++) {
        tach_count += beams[w];
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, tach_count);
    return answer;
}