#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"
#include "parse.h"
const char* DAY9_PART1_ANSWER = "4781377701";
const char* DAY9_PART2_ANSWER = "1470616992";


static int64_t min(int64_t a, int64_t b){
    if (a < b) {
        return a;
    }
    return b;
}

static int64_t max(int64_t a, int64_t b){
    if (a > b) {
        return a;
    }
    return b;
}

struct rect
{
    struct point2 bottom_left;
    struct point2 upper_right;
    int64_t area;
};

void day9(const char* filename){
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

void print_parray(const struct point2* p, const size_t len){
    printf("{");
    for (size_t i = 0; i < len; i++) {
        print_point2(p[i]);
        if (i < len - 1) {
            printf(", ");
        }
    }
    printf("}");
}

int64_t rect_area(struct point2 p1, struct point2 p2){
    int64_t w = 1 + llabs(p2.x - p1.x);
    int64_t h = 1 + llabs(p2.y - p1.y);
    int64_t area = w * h;
    return area;
}

void print_rect(const struct rect* rr){
    printf("Rect: {(%lld,%lld) -> (%lld,%lld)}, area: %lld\n",
           rr->bottom_left.x,
           rr->bottom_left.y,
           rr->upper_right.x,
           rr->upper_right.y,
           rect_area(rr->bottom_left, rr->upper_right)
    );
}

//  ((DAY_08_SIZE - 1) * DAY_08_SIZE >> 1)
char* day9_part1(struct problem_inputs p_i){
    size_t p_num = p_i.count;
    struct point2* points = malloc(sizeof(struct point2) * p_num);
    for (size_t i = 0; i < p_num; i++) {
        struct point2 p = parse_2d_point_from_line(p_i.lines[i]);
        points[i] = p;
    }

    int64_t max_area = -1;
    for (size_t i = 0; i < p_num - 1; i++) {
        for (size_t j = i; j < p_num; j++) {
            if (i == j) { continue; }

            struct point2 p1 = points[i];
            struct point2 p2 = points[j];


            int64_t r_area = rect_area(p1, p2);
            if (r_area > max_area) {
                max_area = r_area;
            }
        }
    }
    free(points);
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, max_area);
    return answer;
}


struct rect build_rect(struct point2 p1, struct point2 p2){
// this is creating bounding corner, not wokring with existing oints

    struct rect rr;


    int64_t lower_x = min(p1.x, p2.x);
    int64_t upper_x = max(p1.x, p2.x);
    int64_t lower_y = min(p1.y, p2.y);
    int64_t upper_y = max(p1.y, p2.y);
    rr.bottom_left.x = lower_x;
    rr.bottom_left.y = lower_y;
    rr.upper_right.x = upper_x;
    rr.upper_right.y = upper_y;
    int64_t r_w = 1 + rr.upper_right.x - rr.bottom_left.x;
    int64_t r_h = 1 + rr.upper_right.y - rr.bottom_left.y;
    rr.area = r_w * r_h;
    return rr;
}

size_t cmp_count=0;
int cmp_rect_by_area(const void* a, const void* b){
    cmp_count++;
    const int64_t left = ((const struct rect*)a)->area;
    const int64_t right = ((const struct rect*)b)->area;
    return (left > right) - (left < right);
}

bool point2_same(struct point2 a, struct point2 b){
    if ((a.x == b.x) && (a.y == b.y)) {
        return true;
    }
    return false;
}


/*
 *  So each pair of points around the loop share a coord (X , Z) (Z, Y) or (Z, Y)(X Z)
 *  We can build a triangle from this triple, getting 3 of 4 point of the rectangle.
 *  From this, we can calculate what the 4th point must be. Then check if that 4th point
 *     is either in point list (i.e. red), or in the range between any adjacent pair green)
 *
 *
 *     XOOOOOOOX
 *     O       |
 *     O
 *     O
 *     X--   X--?-- X
 */
char* day9_part2(struct problem_inputs p_i){
    size_t p_num = p_i.count;
    struct point2* points = malloc(sizeof(struct point2) * p_num);
    for (size_t i = 0; i < p_num; i++) {
        struct point2 p = parse_2d_point_from_line(p_i.lines[i]);
        points[i] = p;
    }

    int64_t max_area = -1;


    const size_t pair_count = 1 + ((p_num - 1) * p_num) / 2;
    struct rect* r_array = malloc(sizeof(struct rect) * pair_count);

    char* bytes = (char*)r_array;

    size_t r_idx=0;
    for (size_t i = 0; i < p_num - 1; i++) {
        for (size_t j = i; j < p_num; j++) {
            if (i == j) { continue; }
            const struct point2 p1 = points[i];
            const struct point2 p2 = points[j];
            const struct rect rr = build_rect(p1, p2);

            r_array[r_idx] = rr;
            r_idx++;
        }
    }
    r_array[pair_count - 1] = build_rect(points[p_num - 1], points[0]);
    print_rect(&r_array[pair_count - 1]);


    printf("pre-sort (cmp_count=%zu)\n", cmp_count);


    qsort(r_array, pair_count, sizeof(struct rect),
          cmp_rect_by_area);


    printf("sort done (cmp_count=%zu)\n", cmp_count);
    print_rect(&r_array[0]);
    print_rect(&r_array[pair_count - 1]);
    free(points);
    free(r_array);
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, max_area);
    return answer;
}
