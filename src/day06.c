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
const char* DAY6_PART2_ANSWER = "0";

// part 1 -> 15_004_115_315 to loow
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
    println();



    struct int64_vec first = parse_line_ints(p_i.lines[0], strlen(p_i.lines[0]));
    struct int64_vec second = parse_line_ints(p_i.lines[1], strlen(p_i.lines[1]));
    struct int64_vec third= parse_line_ints(p_i.lines[2], strlen(p_i.lines[2]));
     struct int64_vec fourth  = parse_line_ints(p_i.lines[3], strlen(p_i.lines[3]));

    // print_int64_vec(first);
    // println();
    // print_int64_vec(second);
    // println();
    // print_int64_vec(third);
    // println();

    printf("first: %lld -> %lld , len=%zu \n", first.arr[0], first.arr[first.len -1], first.len);
    printf("second: %lld -> %lld , len=%zu \n", second.arr[0], second.arr[first.len -1], second.len);
    printf("third: %lld -> %lld , len=%zu \n", third.arr[0], third.arr[third.len -1], third.len);
    printf("fourth: %lld -> %lld , len=%zu \n", fourth.arr[0], fourth.arr[fourth.len -1], fourth.len);

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
    printf("ops: %s\n", ops);
    int64_t total =0;
    for (size_t p =0; p < number_of_operations; p++) {
        int64_t a = first.arr[p];
        int64_t b = second.arr[p];
        int64_t c = third.arr[p];
        int64_t d = fourth.arr[p];
        int64_t value;
        char c_op = ops[p];
        printf("\t %lld %c %lld %c %lld %c %lld =", a,c_op,b,c_op,c,c_op,d);
        if (c_op == '+') {
            value = a + b + c + d;
        }else if (c_op == '*') {
            value = a * b * c * d;
        } else {
            printf("unknown operator: %c\n", c_op);
            exit(-1);
        }
        total += value;
        printf(" %lld  \t total= %lld\n", value, total);

    }



    free(ops);
    free_int64_vec(&first);
    free_int64_vec(&second);
    free_int64_vec(&third);
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, total);
    return answer;
}

char
* day6_part2(struct problem_inputs p_i) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}
