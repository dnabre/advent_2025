#include <stdio.h>
#include <stdlib.h>

#include "io.h"

#include <inttypes.h>
#include <string.h>


char* read_line(FILE* fp) {
    size_t cap = 128;
    size_t len = 0;
    char* buf = malloc(cap);

    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\r') {
            printf("%s:%d, error: carriage return found in input\n", __func__, __LINE__);
            exit(-1);
        }
        if (c == '\n') break;
        if (len + 1 >= cap) {
            cap *= 2;
            char* newbuf = realloc(buf, cap);
            if (!newbuf) {
                free(buf);
                exit(-1);
            }
            buf = newbuf;
        }
        buf[len++] = (char)c;
    }
    if ((len == 0) && (c == EOF)) {
        free(buf);
        return NULL;
    }
    buf[len] = '\0';
    return buf;
}


struct problem_inputs read_by_lines(const char* filename) {
    struct problem_inputs result = {NULL, 0};

    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        perror("read_by_lines, fopen");
        exit(-1);
    }

    size_t capacity = 0;
    char* line;
    while ((line = read_line(fp)) != NULL) {
        if (result.count == capacity) {
            size_t new_cap = capacity == 0 ? 8 : capacity * 2;
            char** new_lines = realloc(result.lines, new_cap * sizeof(char*));
            if (!new_lines) {
                exit(-1);
            }
            result.lines = new_lines;
            capacity = new_cap;
        }
        result.lines[result.count++] = line;
    }
    fclose(fp);
    return result;
}

struct problem_inputs read_full_file_to_lines(const char* filename) {
    struct problem_inputs result = {0};
    size_t file_size;
    char* buffer = read_full_file(filename, &file_size);
    result.lines = lines_from_buffer(buffer, file_size, &(result.count));
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
    result.lines = entries;
    result.count = count;
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

char** lines_from_buffer(char* buffer, const size_t size, size_t* number_of_lines) {
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
            start = buffer + i + 1;
            lines[idx++] = strdup(start);
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

void print_size_t_array(const size_t* arr, const size_t size) {
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

void print_int_pair_range(const struct int_pair r) {
    printf("[%"PRId64 ", %"PRId64"]", r.x, r.y);
}


void print_c_grid(const struct c_grid q) {
    printf("c_grid height: %td, width: %td\n",
        q.num_rows, q.num_cols);
    if (q.g != NULL) {
        for (size_t r = 0; r < q.num_rows; r++) {
            if (q.g[r] != NULL) {
                for (size_t c = 0; c < q.num_cols; c++) {
                    char ch = q.g[r][c];
                    printf("%c", ch);
                }
                println();
            }
            else {
                printf("\t line %zu is NULL\n", r);
            }
        }
    }
    else {
        printf("\t pointer to grid contents NULL");
    }
}

void print_point3(const struct point3 p) {
    printf("[%"PRId64, p.x);
    printf(",%"PRId64, p.y);
    printf(",%"PRId64, p.z);
    printf("]");
}

void print_point2(const struct point2 p) {
    printf("[%"PRId64, p.x);
    printf(",%"PRId64, p.y);
    printf("]");
}

void print_cstr_array( char** v, const size_t size){
    if ((v == NULL) || (size==0)) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < size; i++) {
        printf("\"%s\"", v[i]);
        if (i + 1 < size) {
            printf(", ");
        }
    }
    printf("]");
}