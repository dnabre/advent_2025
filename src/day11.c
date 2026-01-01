#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "ds.h"
#include "io.h"
#include "util.h"
const char* DAY11_PART1_ANSWER = "0";
const char* DAY11_PART2_ANSWER = "0";


void day11(const char* filename){
    const struct problem_inputs day11_lines = read_by_lines(filename);

    printf("Advent of Code, Day 11\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day11_part1(day11_lines);

    printf("\t %s\n", answer_part1);

    // printf("\t part 2: ");
    char* answer_part2 = day11_part2(day11_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY11_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 11, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY11_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY11_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 11, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY11_PART2_ANSWER, answer_part2);
    }


    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

#define C_SPAN 26
bool seen[C_SPAN][C_SPAN][C_SPAN] = {false};
size_t seen_count =0;

char int2char(size_t i) {
    return (char)((unsigned char)i + 'a');
}

bool mark_seen(const char* str){
    if (seen[str[0] - 'a'][str[1] - 'a'][str[2] - 'a']) {
        return true;
    }
    seen[str[0] - 'a'][str[1] - 'a'][str[2] - 'a'] = true;
    seen_count++;
    return false;
}

char* day11_part1(const struct problem_inputs p_i){
    println();
    printf("read %zu lines\n\n", p_i.count);
    size_t mark_count=0;

    for (size_t i = 0; i < p_i.count; i++)
        // size_t i=0;
        {
        const size_t l_len = strlen(p_i.lines[i]);
        struct fstr_vec* pieces = fsplit_on_char(p_i.lines[i], l_len, ' ');

        char first[4];;
        strncpy(first, pieces->arr[0]->str, 3);
        first[3] = '\0';
        if (!mark_seen(first) ) {
            mark_count++;
        }


        // printf("first: \"%s\" (new: %s)\t", first, bool2str(first_new)); println();
        char* rest[pieces->len - 1];
        size_t rest_len = pieces->len - 1;
        for (size_t j = 1; j < pieces->len; j++) {
            rest[j - 1] = strdup(pieces->arr[j]->str);
        }
        free_fstr_vec(pieces);
        // printf("rest: ");
        // print_cstr_array(rest, rest_len); println();
        for (size_t j = 0; j < rest_len; j++) {
            if (!mark_seen(rest[j]) ) {
                mark_count++;
            }
        }




        // printf("rest_len: %zu, seen strings: %zu\n", rest_len, seen_count);

        for (size_t j = 0; j < rest_len; j++) {
            free(rest[j]);
        }
    }

    size_t s_count=0;
    for (size_t x=0; x < C_SPAN; x++) {
        for (size_t y=0; y < C_SPAN; y++) {
            for (size_t z=0; z < C_SPAN; z++) {
                if (seen[x][y][z]) {
                    printf(" %c%c%c  \t %zu \n", int2char(x), int2char(y), int2char(z)  ,s_count);
                    s_count++;
                }

            }
        }
    }
    println();
    printf("seen strings: %zu\n", seen_count);

    printf("mark_count: %zu\n", mark_count);
    println();
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}

char* day11_part2(const struct problem_inputs p_i){
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}
