#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>


#include "days.h"
#include "io.h"


const char* DAY3_PART1_ANSWER = "17109";
const char* DAY3_PART2_ANSWER = "5847";


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
    char* current;
    int64_t total_jolts = 0;
    println();
    for (size_t i = 0; i < line_array.len; i++) {
        current = line_array.inputs[i];
        size_t len = strlen(current);

        // printf("\n|%4zu: [%s], len: %zu|\n\n", i, current, len);


        size_t left, right;

        size_t m_left_p = 0;
        size_t m_right_p = 1;
        char c_left = current[m_left_p];
        char c_right = current[m_right_p];

        int64_t max_jolt = (c_left - '0') * 10 + (c_right - '0');


        for (left = 0; left < len - 1; left++) {
            c_left = current[left];
            for (right = left + 1; right < len; right++) {
                if (right == left) { continue; }
                if ((m_left_p == m_right_p) || (left == right)) {
                    printf("error: left isn't < right, p %zu:%zu, %zu:%zu\n", m_left_p, m_right_p, left, right);
                    exit(-1);
                }
                c_right = current[right];
                int64_t jolts = (c_left - '0') * 10 + (c_right - '0');
                if (jolts > max_jolt) {
                    // printf("new max %lld > %lld,  %zu:%zu %c %c  >  %zu:%zu %c %c\n",
                    // jolts, max_jolt, left,right,c_left,c_right, m_left_p,m_right_p, current[m_left_p], current[m_right_p]);
                    max_jolt = jolts;
                    m_left_p = left;
                    m_right_p = right;
                }
                else {
                    // printf("too low:  %lld > %lld, %zu:%zu %c %c  !<  %zu:%zu %c %c\n",
                    // jolts, max_jolt, left,right,c_left,c_right, m_left_p,m_right_p, current[m_left_p], current[m_right_p]);
                }
            }
        }
        // printf("%3zu: %zu:%zu  is max jolt at %lld\n", i,m_left_p,m_right_p,max_jolt);

        total_jolts += max_jolt;
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, total_jolts);
    return answer;
}

static int64_t get_jolts(size_t* pos_array, char* str, size_t banks);

void print_size_t_array(size_t* arr, size_t size);


char* day3_part2(struct problem_inputs line_array) {
    char* current;
    int64_t total_jolts = 0;
    println();
    const size_t NUM_BANKS = 12;
// size_t line_number = 2;
     for (size_t line_number = 0; line_number < line_array.len; line_number++)
        {
        current = line_array.inputs[line_number];


        // printf("\n|%4zu: [%s], len: %zu|\n\n", i, current, len);

        size_t m_pos[NUM_BANKS];

        for (size_t i = 0; i < NUM_BANKS; i++) {
            m_pos[i] = i;
        }
        printf("initial positions: ");
        print_size_t_array(m_pos, NUM_BANKS);
        printf("jolts: %lld\n", get_jolts(m_pos, current, NUM_BANKS));

        size_t len = strlen(current);
        size_t last_used_position = -1;
        size_t digits_left_to_pick = NUM_BANKS;

        // printf("string length: %zu, num banks: %zu, unused positions: %zu\n", len, NUM_BANKS, len - NUM_BANKS);
        for (size_t current_digit = 0; current_digit < NUM_BANKS; current_digit++) {
            digits_left_to_pick--;
            size_t max_left_position = last_used_position + 1;
            size_t max_right_position = len - digits_left_to_pick -1;

             printf("for digit %zu, checking from %zu to %zu  . len: %zu, NUM_BANKS: %zu \t ",current_digit,  max_left_position, max_right_position, len, NUM_BANKS );
            printf("build so far: ");
            for (size_t j=0; j < current_digit;j++) {
                printf("%c", current[m_pos[j]]);
            }
            println();
            char max = current[max_left_position];
            size_t max_pos = max_left_position;
            printf("\t\tsection: ");
            for (size_t j=0; j < max_left_position; j++) {
                printf("%c", current[j]);
            }
            printf("|");

            for (size_t m_idx = max_left_position; m_idx <= max_right_position; m_idx++) {
                char ch = current[m_idx];
                printf("%c", ch);
                if (ch > max) {
                    max = ch;
                    max_pos = m_idx;
                }
            }
            printf("|");
            for (size_t j=max_right_position+1; j < len; j++) {
                printf("%c", current[j]);
            }
            println();


            printf("\tfound max value: %c at pos: %zu for digit: %zu\n", max, max_pos, current_digit);
            m_pos[current_digit] = max_pos;
            last_used_position = max_pos;
        }


        printf("final positions: ");
        print_size_t_array(m_pos, NUM_BANKS);
        printf("jolts: %lld\n\n", get_jolts(m_pos, current, NUM_BANKS));


        /*
 *  what want to divide the string into NUM_BANKS ranges
 *  for position n,
 *      the range is (n-1)'s positsion + 1 to
 *      number of spaces between that start and number of unused pos (len - NUM_BANKS)
 *  from that range, we select the highest value
 *
 */


        total_jolts += get_jolts(m_pos, current, NUM_BANKS);
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, total_jolts);
    return answer;
}

static int64_t get_jolts(size_t* pos_array, char* str, size_t number_of_banks) {
    size_t c_idx = pos_array[0];


    int64_t jolts = str[c_idx] - '0';
    for (size_t i = 1; i < number_of_banks; i++) {
        c_idx = pos_array[i];
        jolts = (jolts * 10) + (str[c_idx] - '0');
    }
    return jolts;
}


void print_size_t_array(size_t* arr, size_t size) {
    if (arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < size; i++) {
        printf("%zu", arr[i]); // %zu is the correct specifier for size_t
        if (i + 1 < size) {
            printf(", ");
        }
    }
    printf("]");
}
