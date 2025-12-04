#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"


#include "days.h"


// total reorganize this stuff and main function
const char* day_01_test_file = "inputs/2025/day_01_test_01.txt";
const char* day_01_prob_file = "inputs/2025/day_01_input_01.txt";

const char* day_02_test_file = "inputs/2025/day_02_test_01.txt";
const char* day_02_prob_file = "inputs/2025/day_02_input_01.txt";


const char* day_03_test_file = "inputs/2025/day_03_test_01.txt";
const char* day_03_prob_file = "inputs/2025/day_03_input_01.txt";

const char* day_04_test_file = "inputs/2025/day_04_test_01.txt";
const char* day_04_prob_file = "inputs/2025/day_04_input_01.txt";


int main(int argc, char* argv[]) {
    // clock_t start, end, whole_start,whole_end;
    // double elapsed_ms;

    // whole_start = clock();
    // start = clock();
    // day1(day_01_test_file);
    // end = clock();
    // elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    // printf("\t\t\t time: %.3f ms\n", elapsed_ms);
    //
    //
    // start = clock();
    // day2(day_02_prob_file);
    //
    // end = clock();
    // elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    // printf("\t\t\t time: %.3f ms\n", elapsed_ms);

    // start = clock();
    day3(day_03_test_file);

    // end = clock();
    // elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    // printf("\t\t\t time: %.3f ms\n", elapsed_ms);
    //
    // start = clock();
    // day4(day_04_test_file);
    //
    // end = clock();
    // elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    // printf("\t\t\t time: %.3f ms\n", elapsed_ms);
    //
    // whole_end = clock();
    // double whole_elapsed_ms = (double)(whole_end - whole_start) * 1000.0 / CLOCKS_PER_SEC;
    // printf("\t total run time: %.3f ms\n", whole_elapsed_ms);

    return 0;
}