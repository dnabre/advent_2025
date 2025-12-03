#include <stdbool.h>
#include <windows.h>

#include "days.h"
#include "io.h"



const char* DAY1_PART1_ANSWER = "995";
const char* DAY1_PART2_ANSWER = "5847";

const int DIAL_START = 50;
const int DIAL_SIZE = 100;



void day1(const char* filename)
{
    struct line_input day1_lines =  read_full_file_to_lines(filename);

    LARGE_INTEGER freq, start, end;
    double elapsed1, elapsed2;

    QueryPerformanceFrequency(&freq);

    printf("Advent of Code, Day 01\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");

    QueryPerformanceCounter(&start);
    char* answer_part1  = day1_part1(filename);
    QueryPerformanceCounter(&end);
    elapsed1 = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    printf("\t %s\t (%.3f ms)\n", answer_part1, elapsed1 );


    printf("\t part 2: ");
    QueryPerformanceCounter(&start);
    char* answer_part2 = day1_part2(filename);

    QueryPerformanceCounter(&end);
    elapsed2 = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    printf("\t %s\t (%.3f ms)\n", answer_part2, elapsed2);
    printf("    ---------------------------------------------\n");

    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
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

    size_t bytes_read;
    char* input = read_full_file(filename, &bytes_read);

    size_t line_count;
    char** lines = lines_from_buffer(input, bytes_read, &line_count);

    int dial = DIAL_START;
    int clicks = 0;

    for (size_t i = 0; i < line_count; i++)
    {
        char turn_direction = lines[i][0];
        int amount = strtol(lines[i] + 1, NULL, 10);
        int d_mult = 0;
        int final_dial_shift = 0;
        bool do_clicker = false;
        while (amount >= DIAL_SIZE)
        {
            amount -= DIAL_SIZE;
            clicks++;
        }
        if (turn_direction == 'L')
        {
            if (amount < dial)
            {
                dial -= amount;
            }
            else if (amount == dial)
            {
                dial = 0;
                if (amount > 0)
                {
                    clicks++;
                }
            }
            else
            {
                do_clicker = true;
                d_mult = -1;
                final_dial_shift = DIAL_SIZE;
            }
        }
        else //(turn_direction == 'R')
        {

            if (dial + amount < DIAL_SIZE)
            {
                dial += amount;
            }
            else if (dial + amount == DIAL_SIZE)
            {
                dial = 0;
                clicks++;
            }
            else
            {
                do_clicker = true;
                d_mult = 1;
                final_dial_shift = -1 * DIAL_SIZE;
            }
        }


        if (do_clicker)
        {
            if (dial != 0)
            {
                clicks++;
            }

            dial = dial + (d_mult * amount) + final_dial_shift;
        }
    }


    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%d", clicks);

    return answer;
}
