#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"

// answer 999 is too high.

const char* DAY1_PART1_ANSWER = "995";
const char* DAY1_PART2_ANSWER = "5847";

const int DIAL_START = 50;
const int DIAL_SIZE = 100;

void day1(const char* filename)
{
    char* answer_part1 = NULL;
    char* answer_part2 = NULL;

    printf("Advent of Code, Day 01\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    // answer_part1 = day1_part1(filename);
    printf("\t %s\n", answer_part1 != NULL? answer_part1: "" );



    printf("\t part 2: ");
    answer_part2 = day1_part2(filename);
    printf("\t %s\n", answer_part2);
    printf("\t %s\n", answer_part2 != NULL? answer_part2: "" );
    printf("    ---------------------------------------------\n");

    if (answer_part1) { free(answer_part1);};
    if (answer_part2) { free(answer_part2);};
}

char* day1_part1(const char* filename)
{
    size_t bytes_read;
    char* input = read_full_file(filename, &bytes_read);
    size_t line_count;
    char** lines = lines_from_buffer(input, bytes_read, &line_count);


    int dial = DIAL_START;
    int zero_count = 0;

    for (size_t i = 0; i < line_count; i++)
    {
        char direction = lines[i][0];
        int amount = strtol(lines[i] + 1, NULL, 10);
        if (direction == 'L')
        {
            dial = (dial - amount) % DIAL_SIZE;
            while (dial < 0)
            {
                dial = dial + DIAL_SIZE;
            }
        }
        else if (direction == 'R')
        {
            dial = (dial + amount) % DIAL_SIZE;
        }
        else
        {
            printf("\n ERROR invalid direction: %c, %d, from %s\n", direction, amount, lines[i]);
            exit(-1);
        }
        if (dial == 0)
        {
            zero_count++;
        }
    }
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%d", zero_count);
    return answer;
}

char* day1_part2(const char* filename)
{
    printf("\n\t reading from file: %s\n", filename);
    size_t bytes_read;
    char* input = read_full_file(filename, &bytes_read);
    println();
    printf("%zu bytes read from file\n", bytes_read);

    size_t line_count;
    char** lines = lines_from_buffer(input, bytes_read, &line_count);

    int dial = DIAL_START;
    int zero_count = 0;

    for (size_t i = 0; i < line_count; i++)
    {
        char direction = lines[i][0];
        int amount = strtol(lines[i] + 1, NULL, 10);
        if (direction == 'L')
        {
            dial = (dial - amount) % DIAL_SIZE;
            while (dial < 0)
            {
                dial = dial + DIAL_SIZE;
            }
        }
        else if (direction == 'R')
        {
            dial = (dial + amount) % DIAL_SIZE;
        }
        else
        {
            printf("\n ERROR invalid direction: %c, %d, from %s\n", direction, amount, lines[i]);
            exit(-1);
        }
        if (dial == 0)
        {
            zero_count++;
        }
    }
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%d", zero_count);
    return answer;
}
