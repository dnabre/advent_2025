#ifndef ADVENT_2025_DAYS_H
#define ADVENT_2025_DAYS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ANSWER_BUFFER_SIZE  32
#include "main.h"


void day1(const char* filename);
char* day1_part1(struct problem_inputs);
char* day1_part2(struct problem_inputs);

void day2(const char* filename);
char* day2_part1(struct range_inputs);
char* day2_part2(struct range_inputs);


#endif //ADVENT_2025_DAYS_H
