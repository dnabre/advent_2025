#ifndef ADVENT_2025_DAYS_H
#define ADVENT_2025_DAYS_H

#define ANSWER_BUFFER_SIZE  32
#include "main.h"


void day1(const char* filename);
char* day1_part1(struct problem_inputs);
char* day1_part2(struct problem_inputs);

void day2(const char* filename);
char* day2_part1(struct range_inputs);
char* day2_part2(struct range_inputs);

void day3(const char* filename);
char* day3_part1(struct problem_inputs);
char* day3_part2(struct problem_inputs);

void day4(const char* filename);
char* day4_part1(struct problem_inputs);
char* day4_part2(struct problem_inputs);

void day5(const char* filename);
char* day5_part1(struct range_inputs day5_ranges, struct problem_inputs day5_items);
char* day5_part2(struct problem_inputs);


#endif //ADVENT_2025_DAYS_H
