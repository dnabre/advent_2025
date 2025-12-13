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

#define COL_BUFFER_SIZE 16
void day6(const char* filename) {
    struct problem_inputs day6_lines = read_by_lines(filename);

    printf("Advent of Code, Day 06\n");
    printf("    ---------------------------------------------\n");
    // printf("\t part 1: ");
    // char* answer_part1 = day6_part1(day6_lines);
    //
    // printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day6_part2(day6_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    // if (strcmp(answer_part1, DAY6_PART1_ANSWER) != 0) {
    //     fprintf(stderr, "Day 6, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
    //             DAY6_PART1_ANSWER, answer_part1);
    // }
    if (strcmp(answer_part2, DAY6_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 6, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY6_PART2_ANSWER, answer_part2);
    }


    // if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

char* day6_part1(struct problem_inputs p_i) {
    struct int64_vec first = parse_line_ints(p_i.lines[0], strlen(p_i.lines[0]));
    struct int64_vec second = parse_line_ints(p_i.lines[1], strlen(p_i.lines[1]));
    struct int64_vec third = parse_line_ints(p_i.lines[2], strlen(p_i.lines[2]));
    struct int64_vec fourth = parse_line_ints(p_i.lines[3], strlen(p_i.lines[3]));

    size_t number_of_operations = first.len;
    char* ops = malloc(number_of_operations * sizeof(char) + 1);
    ops[number_of_operations] = '\0';
    char* op_line = p_i.lines[4];
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
        int64_t a = first.arr[p];
        int64_t b = second.arr[p];
        int64_t c = third.arr[p];
        int64_t d = fourth.arr[p];
        int64_t value;
        char c_op = ops[p];


        if (c_op == '+') {
            value = a + b + c + d;
        }
        else if (c_op == '*') {
            value = a * b * c * d;
        }
        else {
            printf("unknown operator: %c\n", c_op);
            exit(-1);
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

void print_buffer(char* str) {
    printf("-|");
    for (size_t i=0; i < COL_BUFFER_SIZE; i++) {
        char ch = str[i];
        if (isdigit(ch)) {
            printf("%c", ch);
        } else {
            printf("#");
        }
    }
    printf("|-" );
}

char* day6_part2(struct problem_inputs p_i) {
    println();
    int64_t total = 0;


    size_t num_cols = strlen(p_i.lines[0]);
    size_t num_rows = p_i.count;



    size_t max_cols = 0;
    for (size_t t=0; t < p_i.count; t++ ) {
        size_t this_c = strlen(p_i.lines[t]);
        max_cols = (this_c > max_cols)? this_c: max_cols;
    }
    for (size_t t=0; t < p_i.count; t++ ) {
            size_t old_len = strlen(p_i.lines[t]);
            p_i.lines[t] = realloc(p_i.lines[t], sizeof(char) * max_cols + 1);
            for (size_t cc = old_len; cc < max_cols; cc++) {
                p_i.lines[t][cc]=' ';
            }
            p_i.lines[t][max_cols] = '\0';
    }
    num_cols = max_cols;
    printf("\n -----------------------------\n");
    for (size_t i=0; i < p_i.count; i++) {
        printf("|%s|\t len=%zu\n", p_i.lines[i], strlen(p_i.lines[i]));
    }

    printf("\n -----------------------------\n");




    char COL_BUFFER[COL_BUFFER_SIZE];
    char op = '_';
    struct int64_vec q_numbers;
    init_int64_vec(&q_numbers);
    printf("input size: %zu x %zu \n", num_cols, num_rows);

    for (size_t c = 0; c < num_cols; c++) {
        size_t c_length = 0;
        size_t d_count=0;
        for (size_t r = 0; r < num_rows; r++) {
            char ch = p_i.lines[r][c];
            printf("c: %3zu, r: %3zu, ch: '%c', op='%c', d_l: %zu c_l: %zu, q_number.len: %zu\n", c,r,ch, op,d_count, c_length, q_numbers.len);
            if ((ch == '*') || (ch == '+')) {
                op = ch;
                r++;
            }
            if (isdigit(ch)) {

                COL_BUFFER[d_count] = ch;
                d_count++;

            }

            print_buffer(COL_BUFFER);
            printf("c: %3zu, r: %3zu, ch: '%c', op='%c', d_l: %zu c_l: %zu, q_number.len: %zu\n", c,r,ch, op,d_count, c_length, q_numbers.len);
        }
        COL_BUFFER[d_count] = '\0';
        printf("%4zu: |%s|\n", c, COL_BUFFER);
        if (strlen(COL_BUFFER) == 0 && q_numbers.len > 0) {
            print_int64_vec(q_numbers);
            printf("\t |%c|\t", op);

            int64_t old_total = total;

            if (op == '*') {
                int64_t prod = 1;
                for (size_t i = 0; i < q_numbers.len; i++) {
                    prod = prod * q_numbers.arr[i];
                }
                printf("%lld\n", prod);
                total = total + prod;
            }
            if (op == '+') {
                int64_t sum = 0;
                for (size_t i = 0; i < q_numbers.len; i++) {
                    sum = sum + q_numbers.arr[i];
                }
                printf("%lld\n", sum);
                total = total + sum;
            }


            // printf("o: %8lld -> n: %8lld \t (v=%lld)\n", old_total, total, total - old_total);

            op='_';
            // total += value;
            // printf(" = %lld \t total=%lld\n", value, total);
            free_int64_vec(&q_numbers);
        }
        else {
            int64_t value = strtoll(COL_BUFFER,NULL, 10);
            if (value != 0) {
                push_int64_vec(&q_numbers, value);
            }
            for (size_t i=0; i < COL_BUFFER_SIZE; i++) {
                COL_BUFFER[i]='\0';
            }
        }
    }
    print_int64_vec(q_numbers);
    printf("\t |%c|\n", op);

    int64_t old_total = total;

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


    printf("o: %8lld -> n: %8lld \t (v=%lld)\n", old_total, total, total - old_total);


    // printf("%3zu: |%s|\n", c, COL_BUFFER);


    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, total);
    return answer;
}
