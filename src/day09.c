#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"
#include "parse.h"
const char* DAY9_PART1_ANSWER = "4781377701";
const char* DAY9_PART2_ANSWER = "0";


void day9(const char* filename) {
    struct problem_inputs day9_lines = read_by_lines(filename);

    printf("Advent of Code, Day 09\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day9_part1(day9_lines);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day9_part2(day9_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY9_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 9, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY9_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY9_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 9, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY9_PART2_ANSWER, answer_part2);
    }


    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

void print_parray(struct point2* p, size_t len){
    printf("{");
    for (size_t i=0; i < len; i++) {
        print_point2(p[i]);
        if (i < len-1) {
            printf(", ");
        }
    }
    printf("}");
}
char* day9_part1(struct problem_inputs p_i) {

    size_t p_num = p_i.count;
    struct point2* points = malloc(sizeof(struct point2) * p_num);
    for (size_t i=0; i < p_num; i++) {
        struct point2 p = parse_2d_point_from_line(p_i.lines[i]);
        points[i] = p;
    }

    int64_t max_area = -1;

    // print_parray(points, p_num); println();
    for (size_t i=0; i < p_num -1; i++) {
        for (size_t j=i; j < p_num; j++) {
            if (i == j) { continue;}
            struct point2 pair[2];
            struct point2 p1 = points[i];
            struct point2 p2 = points[j];


            pair[0] = p1;
            pair[1] = p2;
            int64_t w =1 + llabs(p2.x - p1.x);
            int64_t h = 1 + llabs( p2.y - p1.y);
            int64_t area = w * h;
            if (area > max_area) {
                max_area = area;
            }

        }
    }

    free(points);
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, max_area);
    return answer;
}

char* day9_part2(struct problem_inputs p_i) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}