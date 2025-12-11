/**
*  I/O functions.
 *  These should only be functions which are directly operating on input files. Generic data operations may be here
 *  put any problem specific parsing should be in `parse`
 *
 *  Any errors encountered while doing I/O should be treated as fatal, and should exit instead of returning an error
 *  value
 *
 */

#ifndef ADVENT_2025_IO_H
#define ADVENT_2025_IO_H
#include "main.h"
/**
 * Reads line from `fp` file stream, returns it as newly alloc string.
*/
char* read_line(FILE* fp);


/**
 * Read specified `filename` into an array of lines. Array and lines are newly allocated
 *
 */
struct problem_inputs read_by_lines(const char* filename);


/**
 * Read contents of `filename`. on error, program will exit with -1 status
 * The number of bytes read will be placed into `bytes_read`, and the
 * data read will be returned in a newly allocated. A null byte is added to the
 * end of the `buffer`, this is not included in bytes_read
 */
char* read_full_file(const char* filename, size_t* bytes_read);

/**
* Splits a provided `buffer` at newlines, returning an array of those lines as strings
* Number of lines found is put into `number_of_lines`. The strings in the array pointing
* to them is fresh memory. `buffer` is modified and freed (fits with `read_full_file`)
*
*/

char** lines_from_buffer(char* buffer, size_t size, size_t* number_of_lines);

/**
 *  Merges `read_full_file` and `lines_from_buffer`, and bundles result
 */
struct problem_inputs read_full_file_to_lines(const char* filename);

/**
 * Reads a single line file containing entries separated by commas
 * Building an array of the entries, backed into a problem_inputs struct.
 */
struct problem_inputs read_full_from_csv(const char* filename);


inline void println() {
    printf("\n");
}

void print_size_t_array(const size_t* arr, size_t size);
void print_int_pair_range(struct int_pair);
void print_c_grid(const struct c_grid);

// void print_c_grid(const struct c_grid);
#endif //ADVENT_2025_IO_H
