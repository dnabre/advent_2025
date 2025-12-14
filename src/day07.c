#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"
const char* DAY7_PART1_ANSWER = "1656";
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


static void toggle(char* beams, size_t pos, size_t width) {
    if (pos >= width) {
        printf("invalid pos: %zu, doesn't fit in width %zu for beams: %s\n", pos, width, beams);
        exit(-1);
    }
    if (beams[pos] == '0') {
        beams[pos] = '1';
    } else {
        beams[pos] = '0';
    }
}

static void set(char* beams, size_t pos, char on_off, size_t width) {
    if (pos >= width) {
        printf("invalid pos: %zu, doesn't fit in width %zu for beams: %s\n", pos, width, beams);
        exit(-1);
    }
    beams[pos] = on_off;
}

char* day7_part1(struct problem_inputs p_i) {
    println();
    size_t width = strlen(p_i.lines[0]);
    size_t height = p_i.count;
    printf("width: %zu\n", width);

    char** grid = p_i.lines;



    char beams[width+1];
    beams[width] = '\0';

    for (size_t i=0; i < width; i++) {
        beams[i] ='0';
    }


    int64_t split_count=0;
    for (size_t h=0; h < height; h++) {
        // printf("%3zu: \t %s\n", h,grid[h]);
        for (size_t w=0; w < width; w++) {
            char ch = grid[h][w];
            if (ch == 'S') {
                set(beams, w, '1', width);
            }
            if (ch == '^') {
                if ((w == 0) || (w == (width-1))) {
                    printf("splitter on edge h: %zu, w: %zu\n", h,w);
                    exit(-1);
                }
                if (beams[w] == '1') {
                    split_count++;
                    set(beams, w, '0', width);
                    set(beams, w-1, '1', width);
                    set(beams, w+1, '1',width);

                }
            }
        }
        // printf("beams:   %s \t splits: %lld \n", beams, split_count);

    }




    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, split_count);
    return answer;
}

char* day7_part2(struct problem_inputs p_i) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}