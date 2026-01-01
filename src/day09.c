#include "c17_strict.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"
#include "parse.h"
#include "util.h"

const char* DAY9_PART1_ANSWER = "4781377701";
const char* DAY9_PART2_ANSWER = "1470616992";

struct rect {
    struct point2 bottom_left;
    struct point2 upper_right;
    int64_t area;
};

struct line_pair {
    struct point2 start;
    struct point2 end;
};

static int64_t rect_area(const struct point2 p1, const struct point2 p2){
    const int64_t w = 1 + llabs(p2.x - p1.x);
    const int64_t h = 1 + llabs(p2.y - p1.y);
    const int64_t area = w * h;
    return area;
}

static struct rect build_rect(const struct point2 p1, const struct point2 p2){
    struct rect rr;
    rr.bottom_left = p1;
    rr.upper_right = p2;
    rr.area = rect_area(p1, p2);
    return rr;
}

static int cmp_rect_by_area(const void* a, const void* b){
    // a & b flipped from normber order to get reverse sort (decreasing area)
    const int64_t left = ((const struct rect*)b)->area;
    const int64_t right = ((const struct rect*)a)->area;
    return (left > right) - (left < right);
}

void day9(const char* filename){
    const struct problem_inputs day9_lines = read_by_lines(filename);
    struct point2* points = malloc(sizeof(struct point2) * day9_lines.count);
    for (size_t i = 0; i < day9_lines.count; i++) {
        const struct point2 p = parse_2d_point_from_line(day9_lines.lines[i]);
        points[i] = p;
    }

    printf("Advent of Code, Day 09\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day9_part1(day9_lines, points);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day9_part2(day9_lines, points);

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


    free(points);
    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}


char* day9_part1(const struct problem_inputs p_i, const struct point2* points){
    size_t p_num = p_i.count;
    int64_t max_area = -1;
    for (size_t i = 0; i < p_num - 1; i++) {
        for (size_t j = i; j < p_num; j++) {
            if (i == j) { continue; }
            // ReSharper disable once CppDFANullDereference
            const struct point2 p1 = points[i];
            const struct point2 p2 = points[j];
            const int64_t r_area = rect_area(p1, p2);
            if (r_area > max_area) {
                max_area = r_area;
            }
        }
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, max_area);
    return answer;
}


char* day9_part2(const struct problem_inputs p_i, const struct point2* points){
    const size_t p_num = p_i.count;
    const size_t pair_count = 1 + ((p_num - 1) * p_num) / 2;
    struct rect* r_array = malloc(sizeof(struct rect) * pair_count);

    size_t r_idx = 0;
    for (size_t i = 0; i < p_num - 1; i++) {
        for (size_t j = i; j < p_num; j++) {
            if (i == j) { continue; }
            // ReSharper disable once CppDFANullDereference
            const struct point2 p1 = points[i];
            const struct point2 p2 = points[j];
            const struct rect rr = build_rect(p1, p2);
            r_array[r_idx] = rr;
            r_idx++;
        }
    }
    // ReSharper disable once CppDFANullDereference
    r_array[pair_count - 1] = build_rect(points[p_num - 1], points[0]);

    const size_t l_num = p_i.count;
    struct line_pair* lines = malloc(sizeof(struct line_pair) * l_num);
    for (size_t i = 0; i < l_num - 1; i++) {
        lines[i].start = points[i];
        lines[i].end = points[i + 1];
    }
    // Tie last element back to the first
    lines[l_num - 1].start = points[l_num - 1];
    lines[l_num - 1].end = points[0];

    // sort rectangles in decreasing order by area
    qsort(r_array, pair_count, sizeof(struct rect), cmp_rect_by_area);

    int64_t answer2 = -1;
    for (size_t i = 0; i < pair_count; i++) {
        const struct point2 a = r_array[i].bottom_left;
        const struct point2 b = r_array[i].upper_right;
        bool safe = false;
        for (size_t ln = 0; ln < l_num; ln++) {
            const struct point2 line_start = lines[ln].start;
            const struct point2 line_end = lines[ln].end;
            // check to make sure sides of rectangle aren't invalid relative to any of the line
            // this is baeed on assumptions about the input from visualization
            bool left_of_rect = (max_i64(a.x, b.x) <= min_i64(line_start.x, line_end.x));
            bool right_of_rect = (min_i64(a.x, b.x) >= max_i64(line_start.x, line_end.x));
            bool above = (max_i64(a.y, b.y) <= min_i64(line_start.y, line_end.y));
            bool below = (min_i64(a.y, b.y) >= max_i64(line_start.y, line_end.y));
            safe = left_of_rect || right_of_rect || above || below;
            if (!safe) break;
        }
        if (safe) {
            answer2 = r_array[i].area;
            break;
        }
    }

    free(r_array);
    free(lines);
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, answer2);
    return answer;
}
