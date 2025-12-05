#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "io.h"
#include "parse.h"

const char* DAY5_PART1_ANSWER = "635";
const char* DAY5_PART2_ANSWER = "169347417057382";




void day5(const char* filename) {

    struct problem_inputs day5_lines = read_by_lines(filename);
    struct range_inputs day5_ranges = {NULL,0};
    struct problem_inputs day5_items = {NULL, 0};

    split_on_empty_range_item(day5_lines, &day5_ranges, &day5_items);

    printf("Advent of Code, Day 05\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day5_part1(day5_ranges,day5_items);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day5_part2(day5_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY5_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 5, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
            DAY5_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY5_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 5, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
            DAY5_PART2_ANSWER, answer_part2);
    }

    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };

    free_problem_inputs(day5_lines);
    free_range_inputs(day5_ranges);
    free_problem_inputs(day5_items);


}

char* day5_part1(struct range_inputs day5_ranges, struct problem_inputs day5_items){
    size_t fresh_count =0;
    for (size_t i=0; i< day5_items.count; i++) {
        int64_t id = strtoll(day5_items.lines[i],NULL, 10);
        bool food_fresh = false;
        for (size_t j=0; j < day5_ranges.count; j++) {

            int64_t left = day5_ranges.ranges[j].x;
            int64_t right = day5_ranges.ranges[j].y;
            if ((left <= id) && ( id <= right)) {
                food_fresh=true;
                break;
            }
        }
        if (food_fresh) {
            fresh_count++;
        }
    }




    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, fresh_count);
    return answer;
}




char* day5_part2(struct problem_inputs line_array) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, (int64_t)0);
    return answer;
}
