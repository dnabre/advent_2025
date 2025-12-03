#include <stdio.h>
#include <stdlib.h>

#include "io.h"

#include <string.h>


// struct line_input
// {
//     size_t count;
//     char** lines;
// };


struct line_input read_full_file_to_lines(const char* filename)
{
    struct line_input result = {0};

    size_t file_size;
    char* buffer = read_full_file(filename, &file_size);

    result.lines = lines_from_buffer(buffer, file_size, &(result.count));

    return result;
}

char* read_full_file(const char* filename, size_t* bytes_read)
{
    char* buffer = NULL;
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("ERROR: opening file");
        exit(-1);
    }
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    buffer = malloc(size);
    fread(buffer, size, 1, file);
    *bytes_read = size;
    fclose(file);
    return buffer;
}


char** lines_from_buffer(char* buffer, size_t size, size_t* number_of_lines)
{
    if (!buffer)
    {
        exit(-1);
    }
    size_t count = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] == '\n')
        {
            count++;
        }
    }
    if (size > 0 && buffer[size - 1] != '\n')
    {
        count++;
    }

    char** lines = malloc(count * sizeof(char*));
    size_t idx = 0;
    char* start = buffer;

    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            lines[idx++] = strdup(start);
            start = buffer + i + 1;
        }
    }

    if (start < buffer + size)
    {
        lines[idx] = strdup(start);
        idx++;
    }


    *number_of_lines = idx;

    free(buffer);

    return lines;
}
