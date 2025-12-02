#include <stdio.h>
#include "main.h"
#include "io.h"
#include "parse.h"

int main(int argc, char *argv[]) {
    printf("Hello World!\n");
    printf("src and include directories setup\n");
    printf("Project year: %s (header file location test)\n", ADVENT_YEAR);
    int test_number = test_io_functions();
    printf("number from io.c/test_io/function: %d\n",test_number );
    int parse_number = test_parse();
    printf("number from parse.c/test_parse/function: %d\n",parse_number );
    return 0;
}
