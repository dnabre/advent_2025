#include "c17_strict.h"
#include <ctype.h>

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "days.h"
#include "ds.h"
#include "io.h"
#include "parse.h"

const char* DAY6_PART1_ANSWER = "4405895212738";
const char* DAY6_PART2_ANSWER = "7450962489289";

static const size_t PART2_COL_BUFFER_SIZE = 16;

void day6(const char* filename) {
    struct problem_inputs day6_lines = read_by_lines(filename);

    printf("Advent of Code, Day 06\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day6_part1(day6_lines);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day6_part2(day6_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY6_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 6, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY6_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY6_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 6, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY6_PART2_ANSWER, answer_part2);
    }


    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

char* day6_part1(struct problem_inputs p_i) {
    struct int64_vec first = parse_line_ints(p_i.lines[0], strlen(p_i.lines[0]));
    struct int64_vec second = parse_line_ints(p_i.lines[1], strlen(p_i.lines[1]));
    struct int64_vec third = parse_line_ints(p_i.lines[2], strlen(p_i.lines[2]));
    struct int64_vec fourth = parse_line_ints(p_i.lines[3], strlen(p_i.lines[3]));

    const size_t number_of_operations = first.len;
    char* ops = malloc(number_of_operations * sizeof(char) + 1);
    ops[number_of_operations] = '\0';
    const char* op_line = p_i.lines[4];
    size_t idx = 0;
    for (size_t i = 0; i < number_of_operations; i++) {
        char ch_o = op_line[idx];
        while ((ch_o != '*') && (ch_o != '+')) {
            idx++;
            ch_o = op_line[idx];
        }
        ops[i] = ch_o;
        idx++;
    }
    int64_t total = 0;

    for (size_t p = 0; p < number_of_operations; p++) {
        const int64_t a = first.arr[p];
        const int64_t b = second.arr[p];
        const int64_t c = third.arr[p];
        const int64_t d = fourth.arr[p];
        int64_t value;
        const char c_op = ops[p];
        if (c_op == '+') {
            value = a + b + c + d;
        }
        else  { // c_op == '*'
            value = a * b * c * d;
        }
        total += value;
    }

    free(ops);
    free_int64_vec(&first);
    free_int64_vec(&second);
    free_int64_vec(&third);
    free_int64_vec(&fourth);
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, total);
    return answer;
}

char* day6_part2(struct problem_inputs p_i) {
    int64_t total = 0;
    const size_t num_rows = p_i.count;
    size_t max_cols = 0;
    for (size_t t = 0; t < p_i.count; t++) {
        const size_t this_c = strlen(p_i.lines[t]);
        max_cols = (this_c > max_cols) ? this_c : max_cols;
    }
    for (size_t t = 0; t < p_i.count; t++) {
        const size_t old_len = strlen(p_i.lines[t]);
        p_i.lines[t] = realloc(p_i.lines[t], sizeof(char) * max_cols + 1);
        for (size_t cc = old_len; cc < max_cols; cc++) {
            p_i.lines[t][cc] = ' ';
        }
        p_i.lines[t][max_cols] = '\0';
    }
    const size_t num_cols = max_cols;
    char COL_BUFFER[PART2_COL_BUFFER_SIZE];
    char op = '_';
    struct int64_vec q_numbers;
    init_int64_vec(&q_numbers);

    for (size_t c = 0; c < num_cols; c++) {
        size_t d_count = 0;
        for (size_t r = 0; r < num_rows; r++) {
            const char ch = p_i.lines[r][c];
            if ((ch == '*') || (ch == '+')) {
                op = ch;
                r++;
            }
            if (isdigit(ch)) {
                COL_BUFFER[d_count] = ch;
                d_count++;
            }
        }
        COL_BUFFER[d_count] = '\0';

        if (strlen(COL_BUFFER) == 0 && q_numbers.len > 0) {
            if (op == '*') {
                int64_t prod = 1;
                for (size_t i = 0; i < q_numbers.len; i++) {
                    prod = prod * q_numbers.arr[i];
                }
                total = total + prod;
            }
            if (op == '+') {
                int64_t sum = 0;
                for (size_t i = 0; i < q_numbers.len; i++) {
                    sum = sum + q_numbers.arr[i];
                }
                total = total + sum;
            }
            free_int64_vec(&q_numbers);
        }
        else {
            const int64_t value = strtoll(COL_BUFFER,NULL, 10);
            if (value != 0) {
                push_int64_vec(&q_numbers, value);
            }
            for (size_t i = 0; i < PART2_COL_BUFFER_SIZE; i++) {
                COL_BUFFER[i] = '\0';
            }
        }
    }

    if (op == '*') {
        int64_t prod = 1;
        for (size_t i = 0; i < q_numbers.len; i++) {
            prod = prod * q_numbers.arr[i];
        }
        total = total + prod;
    }
    if (op == '+') {
        int64_t sum = 0;
        for (size_t i = 0; i < q_numbers.len; i++) {
            sum = sum + q_numbers.arr[i];
        }
        total = total + sum;
    }


    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, total);
    return answer;
}
