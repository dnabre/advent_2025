#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "days.h"
#include "io.h"

const char* DAY4_PART1_ANSWER = "1370";
const char* DAY4_PART2_ANSWER = "8437";
static const char EMPTY = '.';
static const char FULL = '@';


int64_t count_adjacent_rolls(const struct c_grid* g, ptrdiff_t row, ptrdiff_t col);
struct c_grid build_grid(struct problem_inputs);


void day4(const char* filename) {
    struct problem_inputs day4_lines = read_by_lines(filename);
    struct c_grid grid = build_grid(day4_lines);
    printf("Advent of Code, Day 04\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");

    char* answer_part1 = day4_part1(grid);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");

    char* answer_part2 = day4_part2(grid);

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

    free_c_grid(grid);
    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}


char* day4_part1(const struct c_grid g) {
    int64_t accessible_count = 0;
    for (ptrdiff_t r = 0; r < g.num_rows; r++) {
        for (ptrdiff_t c = 0; c < g.num_cols; c++) {
            char ch = g.g[r][c];
            if (ch != EMPTY) {
                int64_t adj_roll_count = count_adjacent_rolls(&g, r, c);
                if (adj_roll_count < 4) {
                    accessible_count++;
                }
            }
        }
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, accessible_count);
    return answer;
}


char* day4_part2(const struct c_grid g) {
    int64_t removed_count = 0;
    bool changed = true;
    struct c_grid current_grid = dup_c_grid(g);

    while (changed) {
        const struct c_grid new_grid = dup_c_grid(current_grid);
        changed = false;
        for (ptrdiff_t r = 0; r < current_grid.num_rows; r++) {
            for (ptrdiff_t c = 0; c < current_grid.num_cols; c++) {
                char ch = current_grid.g[r][c];
                if (ch != EMPTY) {
                    int64_t adj_roll_count = count_adjacent_rolls(&current_grid, r, c);
                    if (adj_roll_count < 4) {
                        changed = true;
                        new_grid.g[r][c] = EMPTY;
                        removed_count++;
                    }
                }
            }
        }
        free_c_grid(current_grid);
        current_grid = new_grid;
    }
    free_c_grid(current_grid);

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, (int64_t)removed_count);
    return answer;
}


int64_t count_adjacent_rolls(const struct c_grid* g, ptrdiff_t row, ptrdiff_t col) {
    int64_t adj_count = 0;
    for (ptrdiff_t dr = -1; dr <= 1; dr++) {
        for (ptrdiff_t dc = -1; dc <= 1; dc++) {
            if ((dr == 0) && (dc == 0)) {
                continue;
            }
            ptrdiff_t n_row = row + dr;
            ptrdiff_t n_col = col + dc;
            if ((0 <= n_col) && (n_col < g->num_cols) && (0 <= n_row) && (n_row < g->num_rows)) {
                char ch = g->g[n_row][n_col];
                if (ch == FULL) {
                    adj_count++;
                }
            }
        }
    }
    return adj_count;
}

struct c_grid build_grid(struct problem_inputs line_array) {
    struct c_grid g;
    g.num_rows = (ptrdiff_t)line_array.count;
    g.num_cols = (ptrdiff_t)strlen(line_array.lines[0]);
    g.g = malloc(sizeof(char*) * g.num_rows);
    for (size_t h = 0; h < g.num_rows; h++) {
        g.g[h] = malloc(sizeof(char) * g.num_cols + 1);

        char* c_line = line_array.lines[h];
        for (size_t w = 0; w < g.num_cols; w++) {
            char ch = c_line[w];
            g.g[h][w] = ch;
        }
        g.g[h][g.num_cols] = '\0';
    }
    return g;
}


struct c_grid dup_c_grid(const struct c_grid g) {
    struct c_grid ng;
    ng.num_rows = g.num_rows;
    ng.num_cols = g.num_cols;
    ng.g = malloc(sizeof(char*) * g.num_rows);
    if (!ng.g) {
        printf("unable to allocate n_grid in dup_c_grid\n");
        exit(-1);
    }
    for (size_t r = 0; r < g.num_rows; r++) {
        ng.g[r] = malloc(sizeof(char) * g.num_cols + 1);
        if (!ng.g[r]) {
            printf("unable to allocate row %zu in dup_c_grid\n", r);
            exit(-1);
        }
        for (size_t c = 0; c < g.num_cols; c++) {
            char ch = g.g[r][c];
            ng.g[r][c] = ch;
        }

        ng.g[r][g.num_cols] = '\0';
    }

    return ng;
}


void free_c_grid(struct c_grid g) {
    for (size_t l = 0; l < g.num_rows; l++) {
        free(g.g[l]);
    }
    free(g.g);
}