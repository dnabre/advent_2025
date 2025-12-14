#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "ds.h"
#include "io.h"
#include "parse.h"
const char* DAY8_PART1_ANSWER = "0";
const char* DAY8_PART2_ANSWER = "0";


void day8(const char* filename) {
    struct problem_inputs day8_lines;
    // need to parse CSV before passing on to problems.

    printf("Advent of Code, Day 08\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day8_part1(day8_lines);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day8_part2(day8_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY8_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 8, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY8_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY8_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 8, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY8_PART2_ANSWER, answer_part2);
    }


    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

struct edge{
    int64_t dist;
    size_t p1_pid;
    size_t p2_pid;
};

struct point{
    int64_t x;
    int64_t y;
    int64_t z;
};


static int64_t calc_sqr_distance(struct point p1, struct point p2) {
    int64_t dx = p1.x - p2.x;
    int64_t dy = p1.y - p2.y;
    int64_t dz = p1.z - p2.z;

    // squaring is a monotonic function for positive values, so n1 > n2 <=> n1^2 > n2^2
    // overhead of sqrt isn't a problem here, just don't want to be bother floating point values or an integer sqrt
    return  (dx*dx) + (dy * dy) + (dz * dz);
}

char* day8_part1(struct problem_inputs p_i) {
    for (size_t l=0; l < p_i.count; l++) {
        printf("%3zu: %s\n", l, p_i.lines[l]);
    }
    const size_t number_of_points = p_i.count;
    size_t forest_id_by_pid[number_of_points];
    for (size_t i=0; i < number_of_points; i++) {
        forest_id_by_pid[i] =i ;
    }

    // loop over input, setting points.
    struct point points[number_of_points];
    for (size_t pid=0; pid < number_of_points; pid++) {
        struct int64_vec pv =  parse_line_ints(p_i.lines[pid], strlen(p_i.lines[pid]));
        struct point p_new = {pv.arr[0], pv.arr[1], pv.arr[2]};
        free_int64_vec(&pv);
        points[pid] = p_new;

    }

    // create and fill array of possible edges with distances
    size_t edge_count=0;
    struct edge dists[number_of_points * number_of_points];
    for (size_t p1=0; p1 < number_of_points; p1) {
        for (size_t p2=p1 + 1; p2 < number_of_points; p2++ ) {
            if (p1 == p2) {
                printf("ERROR: p1==p2 (%lld == %lld)  edge_count: %zu\n", p1,p2, edge_count );
                exit(-1);
            }
            if (p1 > p2) {
                printf("ERROR: p1>p2 (%lld > %lld)  edge_count: %zu\n", p1,p2, edge_count );
                exit(-1);
            }


            dists[edge_count].p1_pid = p1;
            dists[edge_count].p2_pid = p2;
            dists[edge_count].dist = calc_sqr_distance(points[p1], points[p2]);
            edge_count++;
        }
    }
    printf("edge_count: %zu   (guess: %zu) \n", edge_count, number_of_points * number_of_points - number_of_points);
    //



    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}

char* day8_part2(struct problem_inputs p_i) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}