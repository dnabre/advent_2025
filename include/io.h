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

/**
 * Read contents of `filename`. on error, program will exit with -1 status
 * The number of bytes read will be placed into `bytes_read`, and the
 * data read will be returned in a newly allocated.
 */
char* read_full_file(const char* filename, size_t* bytes_read);

/**
* Splits a provided `buffer` at newlines, returning an array of those lines as strings
* Number of lines found is put into `number_of_lines`. The strings in the array pointing
* to them is fresh memory. `buffer` is modified and freed (fits with `read_full_file`)
*
*/

char** lines_from_buffer( char* buffer, size_t size, size_t* number_of_lines);

/**
 *  Merges `read_full_file` and `lines_from_buffer`, and bundles result
 */
struct line_input read_full_file_to_lines(const char* filename);

static inline void println()
{
  printf("\n");
}


struct line_input
{
    size_t count;
    char** lines;
};
#endif //ADVENT_2025_IO_H