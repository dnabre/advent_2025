#include <inttypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "ds.h"
#include "io.h"


const char* DAY10_PART1_ANSWER = "0";
const char* DAY10_PART2_ANSWER = "0";


void day10(const char* filename){
    const struct problem_inputs day10_lines = read_by_lines(filename);

    printf("Advent of Code, Day 10\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day10_part1(day10_lines);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day10_part2(day10_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY10_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 10, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY10_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY10_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 10, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY10_PART2_ANSWER, answer_part2);
    }


    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

/*
 * input limits
 *  number of lights: 10
 *  number of button sets: 13
 *  number of machines : 167
 */


typedef uint16_t b_t;
inline b_t bit_to_on(b_t b, size_t i){
    return b | (b_t)(1u << i);
}

inline b_t bit_to_off(b_t b, size_t i){
    return b & (b_t)~(1u << i);
}

inline b_t bit_toggle(b_t b, size_t i){
    return b ^ (b_t)(1u << i);
}

inline bool get_bit(b_t b, size_t i){
    return (b >> i) & 1u;
}

void print_as_bits(b_t x){
    for (int i = sizeof(x)*CHAR_BIT - 1; i >= 0; --i)
        putchar((x >> i) & 1 ? '1' : '0');
}


void print_bits_u16(uint16_t x)
{
    for (int i = 15; i >= 0; --i) {
        putchar((x >> i) & 1 ? '1' : '0');
    }
}

struct wiring {
    size_t* offset;
    size_t len;
};

struct machine {
    b_t b_start;
    size_t b_len;
    struct wiring* wirings;
    size_t w_len;
};

// allocate struct fstr_vec
struct fstr_vec* fsplit_on_spaces(const char* str, const size_t len){
    size_t count = 0;
    // count number of pieces
    size_t i = 0;
    while (i < len) {
        while (i < len && str[i] == ' ') {
            i++;
        }
        if (i == len) {
            break;
        }
        count++;
        while (i < len && str[i] != ' ') {
            i++;
        }
    }
    // allocte and init struct fstr_vec
    struct fstr_vec* out = malloc(sizeof(struct fstr_vec));
    init_fstr_vec_n(out, count);
    if (count == 0) {
        return out;
    }
    // find pieces and insert into out
    size_t current = 0;
    size_t k = 0;
    while (current < len && k < count) {
        while (current < len && str[current] == ' ') {
            current++;
        }
        if (current == len) {
            break;
        }
        // at piece start
        const size_t start = current;
        while (current < len && str[current] != ' ') {
            current++;
        }
        const size_t piece_len = current - start;
        push_fstr_vec_cn(out, &str[start], piece_len);
        k++;
    }
    return out;
}

const char LIGHT_ON = '#';
const char LIGHT_OFF= '.';








b_t parse_lights(const fstring*  fs){
    size_t count = fs->len -2 ; // subtract out brackets
    b_t b = 0;
    for (size_t i=0; i < count; i++) {
        if (fs->str[i] == LIGHT_ON) {
            b = bit_to_on(b, i);
        }


    }

    return 0;
}

char* day10_part1(const struct problem_inputs p_i){
    println();
    struct machine m_array[p_i.count];
    for (size_t i = 0; i < p_i.count; i++) {
        char* ln = p_i.lines[i];
        const size_t len = strlen(ln);
        m_array[i].b_start = 0;
        size_t n_pieces;
        // fstring* pieces = split_on_space(strdup(ln), len, &n_pieces);
         struct fstr_vec* pieces = fsplit_on_spaces(ln, len);
        b_t bstart = parse_lights(pieces->arr[0]);

        print_fstr_vec(pieces);



        println();
        printf("%3zu: \t %s \t len: %zu\n\n", i, ln, len);
        free_fstr_vec(pieces);
    };


    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}

char* day10_part2(const struct problem_inputs p_i){
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}
