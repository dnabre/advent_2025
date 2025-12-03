#include <stdio.h>
#include <stdlib.h>

#include "io.h"

#include <string.h>

//
// char* read_full_file(const char* filename, size_t* bytes_read)
// {
//     char *buffer;
//     FILE *fh = fopen("readentirefile.c", "rb");
//     if ( fh != NULL )
//     {
//         fseek(fh, 0L, SEEK_END);
//         long s = ftell(fh);
//         rewind(fh);
//         buffer = malloc(s);
//         if ( buffer != NULL )
//         {
//             fread(buffer, s, 1, fh);
//             // we can now close the file
//             fclose(fh); fh = NULL;
//
//             // do something, e.g.
//             fwrite(buffer, s, 1, stdout);
//
//             free(buffer);
//         }
//         if (fh != NULL) fclose(fh);
//     }
//     return EXIT_SUCCESS;
// }


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
        size_t count = 0;
        for (size_t i = 0; i < size; i++) {
            if (buffer[i] == '\n') {
                count++;
            }
        }
        if (size > 0 && buffer[size - 1] != '\n') {
            count++;
        }

        char **lines = malloc(count * sizeof (char*));
        size_t idx = 0;
        char *start = buffer;

        for (size_t i = 0; i < size; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                lines[idx++] = strdup(start);
                start = buffer + i + 1;
            }
        }

        if (start < buffer + size) {
            lines[idx] = strdup(start);
            idx++;
        }


        *number_of_lines = idx;

        free(buffer);

        return lines;
    }



