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
const char* day_04_test2_file = "inputs/2025/day_04_test_02.txt";
const char* day_04_prob_file = "inputs/2025/day_04_input_01.txt";

const char* day_05_test_file = "inputs/2025/day_05_test_01.txt";
const char* day_05_prob_file = "inputs/2025/day_05_input_01.txt";


int main(int argc, char* argv[]) {



    // clock_t whole_start = clock();
    clock_t start = clock();
    clock_t end;
    double elapsed_ms;
    // day1(day_01_prob_file);
    // clock_t end = clock();
    // double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    // printf("\t\t\t time: %.3f ms\n", elapsed_ms);
    //
    //
    // start = clock();
    // day2(day_02_prob_file);
    //
    // end = clock();
    // elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    // printf("\t\t\t time: %.3f ms\n", elapsed_ms);
    //
    // start = clock();
    // day3(day_03_prob_file);
    //
    // end = clock();
    // elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    // printf("\t\t\t time: %.3f ms\n", elapsed_ms);
    //
     start = clock();
    day4(day_04_test2_file);

     end = clock();
     elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
     printf("\t\t\t time: %.3f ms\n", elapsed_ms);

    //
    // end = clock();
    // elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    // printf("\t\t\t time: %.3f ms\n", elapsed_ms);
    //
    // start = clock();
    // day5(day_05_prob_file);
    //
    // end = clock();
    // elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    // printf("\t\t\t time: %.3f ms\n", elapsed_ms);
    //
    //
    //
    //
    // clock_t whole_end = clock();
    // double whole_elapsed_ms = (double)(whole_end - whole_start) * 1000.0 / CLOCKS_PER_SEC;
    // printf("  total of days run time: %.3f ms\n", whole_elapsed_ms);
    //
    // return 0;
}


void free_problem_inputs(struct problem_inputs arr) {
    for (size_t i=0; i < arr.count; i++) {
        free(arr.lines[i]);
    }
    arr.count=0;
    free(arr.lines);
}
void free_range_inputs(struct range_inputs arr) {
    free(arr.ranges);
    arr.count=0;
}

