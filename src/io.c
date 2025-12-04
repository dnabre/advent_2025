#include <stdio.h>
#include <stdlib.h>

#include "io.h"

#include <string.h>


struct problem_inputs read_full_file_to_lines(const char* filename) {
    struct problem_inputs result = {0};
    size_t file_size;
    char* buffer = read_full_file(filename, &file_size);
    result.inputs = lines_from_buffer(buffer, file_size, &(result.len));
    return result;
}

struct problem_inputs read_full_from_csv(const char* filename) {
    size_t file_size;
    char* buffer = read_full_file(filename, &file_size);
    size_t count = 1;
    for (size_t i = 0; i < file_size; i++) {
        if (buffer[i] == ',') {
            count++;
        }
    }
    char** entries = malloc(count * sizeof(char*));
    char* start = buffer;

    size_t idx = 0;
    for (size_t i = 0; i < file_size; i++) {
        if (buffer[i] == ',') {
            buffer[i] = '\0';
            entries[idx++] = strdup(start);
            start = buffer + i + 1;
        }
    }
    if (idx < count) {
        entries[idx] = strdup(start);
    }
    free(buffer);
    struct problem_inputs result = {0};
    result.inputs = entries;
    result.len = count;
    return result;
}


char* read_full_file(const char* filename, size_t* bytes_read) {
    char* buffer = NULL;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("ERROR: opening file");
        exit(-1);
    }
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    buffer = malloc(size + 1);
    buffer[size] = '\0';
    fread(buffer, size, 1, file);
    *bytes_read = size;
    fclose(file);
    return buffer;
}

char** lines_from_buffer(char* buffer, size_t size, size_t* number_of_lines) {
    if (!buffer) {
        exit(-1);
    }
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (buffer[i] == '\n') {
            count++;
        }
    }
    if (size > 0 && buffer[size - 1] != '\n') {
        count++;
    }

    char** lines = malloc(count * sizeof(char*));
    size_t idx = 0;
    char* start = buffer;

    for (size_t i = 0; i < size; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';

            lines[idx++] = strdup(start);

            size_t len = strlen(lines[idx-1]);
            if (lines[idx-1][len] != '\0') {
                printf("while splitting buffer into lines, final string is not null-terminated");
            }

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

void print_size_t_array(const size_t* arr, size_t size) {
    if (arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < size; i++) {
        printf("%zu", arr[i]); // %zu is the correct specifier for size_t
        if (i + 1 < size) {
            printf(", ");
        }
    }
    printf("]");
}