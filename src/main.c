#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"


#include "days.h"


const char* day_01_test_file = "inputs/2025/day_01_test_01.txt";
const char* day_01_prob_file = "inputs/2025/day_01_input_01.txt";

const char* day_02_test_file = "inputs/2025/day_02_test_01.txt";
const char* day_02_prob_file = "inputs/2025/day_02_input_01.txt";


int main(int argc, char* argv[]) {
    day1(day_01_prob_file);


    clock_t start = clock();


    day2(day_02_prob_file);

    clock_t end = clock();


    double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

    printf("\t\t\t time: %.3f ms\n", elapsed_ms);
}