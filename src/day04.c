#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "days.h"
#include "io.h"

const char* DAY4_PART1_ANSWER = "17109";
const char* DAY4_PART2_ANSWER = "169347417057382";


void day4(const char* filename) {
    struct problem_inputs day4_lines = read_by_lines(filename);


    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day4_part1(day4_lines);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day4_part2(day4_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY4_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 4, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY4_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY4_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 4, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY4_PART2_ANSWER, answer_part2);
    }

    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

// for (size_t i =0 ; i < line_array.count; i++) {
//
//
//     printf("%3zu: %s \t l: %zu \n", i, line_array.lines[i], strlen(line_array.lines[i]));
// }




void arr_alloc (size_t x, size_t y, char(**aptr)[x][y])
{
    *aptr = malloc( sizeof(char[x][y]) ); // allocate a true 2D array

}

void arr_fill (size_t x, size_t y, char array[x][y])
{
    for(size_t i=0; i<x; i++)
    {
        for(size_t j=0; j<y; j++)
        {
            array[i][j] = (char)j + 1;
        }
    }
}

void arr_print (size_t x, size_t y, char array[x][y])
{
    for(size_t i=0; i<x; i++)
    {
        for(size_t j=0; j<y; j++)
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}








char* day4_part1(struct problem_inputs line_array) {
    printf("line_array.count=%zu\n", line_array.count);

    // struct c_grid grid;
    // grid.height = line_array.count;
    // grid.width = strlen(line_array.lines[0]);
    // grid.g=NULL;
    // cg->height = line_array.count;
    // cg->width = strlen(line_array.lines[0]);
    //
    // cg->g = malloc(sizeof(char[cg->height][cg->width]));
    // //cg->g= malloc((cg->height) * (cg->width) * sizeof(char));
    // if (cg->g == NULL) {
    //     perror("cg->g malloc failed");
    // }
    // for (size_t h = 0; h < cg->height; h++) {
    //     for (size_t w = 0; w < cg->width; w++) {
    //         cg->g[h][w] = line_array.lines[h][w];
    //     }
    // }











    printf("before print_c_grid call\n");



    printf("post print_c_grid call\n");


    // free_c_grid(cg);
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, (int64_t)0);
    return
        answer;
}

#define DAY_04_PART_02_NUMBER_OF_BANKS 12

char* day4_part2(struct problem_inputs line_array) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, (int64_t)0);
    return answer;
}
