#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"

const char* DAY3_PART1_ANSWER = "17109";
const char* DAY3_PART2_ANSWER = "169347417057382";


void day3(const char* filename) {
    struct problem_inputs day3_lines = read_full_file_to_lines(filename);
    // Lines aren't always properly number terminated, workaround for today.

    for (size_t i = 0; i < day3_lines.len; i++) {
        size_t should_be_null = 0;
        while (isdigit(day3_lines.inputs[i][should_be_null])) {
            should_be_null++;
        }

        // day3_lines.inputs[i][15]='\0';
        day3_lines.inputs[i][should_be_null] = '\0';
    }


    printf("Advent of Code, Day 03\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day3_part1(day3_lines);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day3_part2(day3_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY3_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 3, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY3_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY3_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 3, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY3_PART2_ANSWER, answer_part2);
    }


    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}


char* day3_part1(struct problem_inputs line_array) {
    int64_t total_jolts = 0;

    for (size_t i = 0; i < line_array.len; i++) {
        char* current = line_array.inputs[i];
        size_t len = strlen(current);


        size_t m_left_p = 0;
        size_t m_right_p = 1;
        char c_left = current[m_left_p];
        char c_right = current[m_right_p];

        int64_t max_jolt = (c_left - '0') * 10 + (c_right - '0');


        for (size_t left = 0; left < len - 1; left++) {
            c_left = current[left];
            for (size_t right = left + 1; right < len; right++) {
                if (right == left) { continue; }
                if ((m_left_p == m_right_p) || (left == right)) {
                    printf("error: left isn't < right, p %zu:%zu, %zu:%zu\n", m_left_p, m_right_p, left, right);
                    exit(-1);
                }
                c_right = current[right];
                int64_t jolts = (c_left - '0') * 10 + (c_right - '0');
                if (jolts > max_jolt) {
                    max_jolt = jolts;
                    m_left_p = left;
                    m_right_p = right;
                }
            }
        }
        total_jolts += max_jolt;
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, total_jolts);
    return answer;
}

static int64_t get_jolts(const size_t* pos_array, const char* str);


#define DAY_03_PART_02_NUMBER_OF_BANKS 12

char* day3_part2(struct problem_inputs line_array) {
    int64_t total_jolts = 0;
    // const size_t DAY_03_PART_02_NUMBER_OF_BANKS = 12;

    for (size_t line_number = 0; line_number < line_array.len; line_number++) {
        char* current = line_array.inputs[line_number];

        size_t m_pos[DAY_03_PART_02_NUMBER_OF_BANKS];

        for (size_t i = 0; i < DAY_03_PART_02_NUMBER_OF_BANKS; i++) {
            m_pos[i] = i;
        }

        size_t len = strlen(current);
        size_t last_used_position = -1;
        size_t digits_left_to_pick = DAY_03_PART_02_NUMBER_OF_BANKS;

        for (size_t current_digit = 0; current_digit < DAY_03_PART_02_NUMBER_OF_BANKS; current_digit++) {
            digits_left_to_pick--;
            size_t max_left_position = last_used_position + 1;
            size_t max_right_position = len - digits_left_to_pick - 1;

            char max = current[max_left_position];
            size_t max_pos = max_left_position;

            for (size_t m_idx = max_left_position; m_idx <= max_right_position; m_idx++) {
                char ch = current[m_idx];
                if (ch > max) {
                    max = ch;
                    max_pos = m_idx;
                }
            }
            m_pos[current_digit] = max_pos;
            last_used_position = max_pos;
        }
        total_jolts += get_jolts(m_pos, current);
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, total_jolts);
    return answer;
}

static int64_t get_jolts(const size_t* pos_array, const char* str) {
    size_t c_idx = pos_array[0];


    int64_t jolts = str[c_idx] - '0';
    for (size_t i = 1; i < DAY_03_PART_02_NUMBER_OF_BANKS; i++) {
        c_idx = pos_array[i];
        jolts = (jolts * 10) + (str[c_idx] - '0');
    }
    return jolts;
}
