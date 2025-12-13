#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"




#include "days.h"


// total reorganize this stuff and main function


const char* day_01_test_file = "inputs/2025/day_01_test_01.txt";
const char* day_01_input_file = "inputs/2025/day_01_input_01.txt";

const char* day_02_test_file = "inputs/2025/day_02_test_01.txt";
const char* day_02_input_file = "inputs/2025/day_02_input_01.txt";

const char* day_03_test_file = "inputs/2025/day_03_test_01.txt";
const char* day_03_input_file = "inputs/2025/day_03_input_01.txt";

const char* day_04_test_file = "inputs/2025/day_04_test_01.txt";
const char* day_04_test2_file = "inputs/2025/day_04_test_02.txt";
const char* day_04_input_file = "inputs/2025/day_04_input_01.txt";

const char* day_05_test_file = "inputs/2025/day_05_test_01.txt";
const char* day_05_input_file = "inputs/2025/day_05_input_01.txt";

const char* day_06_test_file = "inputs/2025/day_06_test_01.txt";
const char* day_06_test2_file = "inputs/2025/day_06_test_02.txt";
const char* day_06_input_file = "inputs/2025/day_06_input_01.txt";

const char* day_07_test_file = "inputs/2025/day_07_test_01.txt";
const char* day_07_input_file = "inputs/2025/day_07_input_01.txt";

const char* day_08_test_file = "inputs/2025/day_08_test_01.txt";
const char* day_08_input_file = "inputs/2025/day_08_input_01.txt";

const char* day_09_test_file = "inputs/2025/day_09_test_01.txt";
const char* day_09_input_file = "inputs/2025/day_09_input_01.txt";

const char* day_10_test_file = "inputs/2025/day_10_test_01.txt";
const char* day_10_input_file = "inputs/2025/day_10_input_01.txt";

const char* day_11_test_file = "inputs/2025/day_11_test_01.txt";
const char* day_11_input_file = "inputs/2025/day_11_input_01.txt";

const char* day_12_test_file = "inputs/2025/day_12_test_01.txt";
const char* day_12_input_file = "inputs/2025/day_12_input_01.txt";


void run_all() {
    clock_t whole_start = clock();

    day1(day_01_input_file);
    day2(day_02_input_file);
    day3(day_03_input_file);
    day4(day_04_input_file);
    day5(day_05_input_file);
    day6(day_06_input_file);
    day7(day_07_input_file);
    day8(day_08_input_file);
    day9(day_09_input_file);
    day10(day_10_input_file);

    // day11(day_11_input_file);
    // day12(day_12_input_file);


    clock_t whole_end = clock();
    double whole_elapsed_ms = (double)(whole_end - whole_start) * 1000.0 / CLOCKS_PER_SEC;
    printf("\n  Total runtime of all days: %.3f ms\n", whole_elapsed_ms);
}

// #define  RUN_ALL true

int main(int argc, char* argv[]) {

#ifdef RUN_ALL

        run_all();
#else

    clock_t start = clock();
        // day6(day_06_test_file);

    day6(day_06_input_file);

        clock_t end = clock();
        double elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
        printf("\t\t\t time: %.3f ms\n", elapsed_ms);
#endif

    return 0;
}


void free_problem_inputs(struct problem_inputs arr) {
    for (size_t i = 0; i < arr.count; i++) {
        free(arr.lines[i]);
    }
    arr.count = 0;
    free(arr.lines);
}

void free_range_inputs(struct range_inputs arr) {
    free(arr.ranges);
    arr.count = 0;
}
