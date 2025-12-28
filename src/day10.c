#include <inttypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "ds.h"
#include "io.h"


#define PRINT_INT(x) \
printf(_Generic((x), \
int8_t:   "%" PRId8, \
uint8_t:  "%" PRIu8, \
int16_t:  "%" PRId16, \
uint16_t: "%" PRIu16, \
int32_t:  "%" PRId32, \
uint32_t: "%" PRIu32, \
int64_t:  "%" PRId64, \
uint64_t: "%" PRIu64, \
default:  "<?>"), \
(x))


const char* DAY10_PART1_ANSWER = "429"; //432
const char* DAY10_PART2_ANSWER = "17759"; //17983
typedef uint16_t b_t;

/*
 * input limits
 *  number of lights: 10
 *  number of button sets: 13
 *  number of machines : 167
 */


uint16_t bswap16(const uint16_t x){
    return (uint16_t)((x >> 8) | (x << 8));
}

struct state {
    size_t total_num_press;
    size_t* pressed;
};

struct machine {
    b_t goal;
    size_t b_num;
    size_t w_num;
    size_t** w_array;
    size_t* j_array;
};

struct machine* c_machine = NULL;

// allocate struct fstr_vec
struct fstr_vec* fsplit_on_char(const char* str, const size_t len, const char ch){
    size_t count = 0;
    // count number of pieces
    size_t i = 0;
    while (i < len) {
        while (i < len && str[i] == ch) {
            i++;
        }
        if (i == len) {
            break;
        }
        count++;
        while (i < len && str[i] != ch) {
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
        while (current < len && str[current] == ch) {
            current++;
        }
        if (current == len) {
            break;
        }
        // at piece start
        const size_t start = current;
        while (current < len && str[current] != ch) {
            current++;
        }
        const size_t piece_len = current - start;
        push_fstr_vec_cn(out, &str[start], piece_len);
        k++;
    }
    return out;
}

const char LIGHT_ON = '#';
const char LIGHT_OFF = '.';





inline b_t bit_toggle(const b_t b, const size_t i){
    return b ^ (b_t)(1u << i);
}

inline bool get_bit(const b_t b, const size_t i){
    return (b >> i) & 1u;
}


inline b_t bit_to_on(const b_t b, const size_t i){
    // return b | (b_t)(1u << i);

    return b | ((b_t)1 << i);
}

inline b_t bit_to_off(const b_t b, const size_t i){
    // return b & (b_t)~(1u << i);
    return b & ~((b_t)1 << i);
}

void print_bits_u16(const uint16_t x){
    for (size_t i = 0; i < 16; i++) {
        if (get_bit(x, i)) {
            putchar('1');
        } else {
            putchar('0');
        }
    }
}

b_t parse_lights(const fstring* fs){
    b_t b = 0;
    size_t b_idx = 0;
    for (size_t i = 1; i < fs->len - 1; i++) {
        if (fs->str[i] == LIGHT_ON) {
            b = bit_to_on(b, b_idx);
        } else {
            b = bit_to_off(b, b_idx);
        }
        b_idx++;
    }
    return b;
}

void print_bt(const b_t b, const size_t n){
    for (size_t i = 0; i < n; i++) {
        if (get_bit(b, i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
}


void print_machine(const struct machine* m){
    printf("machine:\n");
    printf("\t goal  : ");
    print_bits_u16(m->goal);
    println();
    printf("\t b_num : %zu\n", m->b_num);
    printf("\t w_num : %zu\n", m->w_num);
    printf("\t wirings:\n");
    for (size_t i = 0; i < m->w_num; i++) {
        printf("\t\t");
        print_size_t_array(m->w_array[i], m->b_num);
        println();
    }
    printf("\t jolts : ");
    print_size_t_array(m->j_array, m->b_num);
    println();
    printf("\n-----------------------------------------\n");
}


void day_parse(struct machine* m_array, const struct problem_inputs* p_i){
    for (size_t i = 0; i < p_i->count; i++) {
        char* ln = p_i->lines[i];
        const size_t len = strlen(ln);
        m_array[i].goal = 0;

        struct fstr_vec* pieces = fsplit_on_char(ln, len, ' ');
        size_t b_num = strlen(pieces->arr[0]->str) - 2;
        b_t bstart = parse_lights(pieces->arr[0]);
        size_t w_num = pieces->len - 2;

        m_array[i].goal = bstart;
        m_array[i].b_num = b_num;
        m_array[i].w_num = w_num;

        size_t** wiring_array = malloc(sizeof(size_t*) * w_num);
        for (size_t w_idx = 0; w_idx < w_num; w_idx++) {
            fstring* piece = fstr_dup(pieces->arr[w_idx + 1]);
            // printf("w_idx: %3zu, \t |%s| (len=%zu)\n", w_idx, piece->str, piece->len);
            struct fstr_vec* buttons = fsplit_on_char(piece->str + 1, piece->len - 2, ',');
            // print_fstr_vec(buttons);
            size_t* w_v = malloc(sizeof(size_t) * b_num);
            wiring_array[w_idx] = w_v;
            for (size_t w = 0; w < buttons->len; w++) {
                size_t r = strtoll(buttons->arr[w]->str, NULL, 10);
                w_v[w] = r;
            }
            for (size_t w = buttons->len; w < b_num; w++) {
                w_v[w] = 0;
            }
            free_fstr_vec(buttons);
        }
        fstring* j_string = pieces->arr[pieces->len - 1];
        struct fstr_vec* jolts = fsplit_on_char(j_string->str + 1, j_string->len - 2, ',');

        m_array[i].j_array = malloc(sizeof(size_t) * b_num);
        for (size_t j = 0; j < jolts->len; j++) {
            size_t jj = strtoll(jolts->arr[j]->str, NULL, 10);
            m_array[i].j_array[j] = jj;
        }
        free_fstr_vec(jolts);
        free_fstr_vec(pieces);
        m_array[i].w_array = wiring_array;
    }
}

void free_machine(const struct machine* m){
    for (size_t i = 0; i < m->w_num; i++) {
        free(m->w_array[i]);
    }
    free(m->w_array);
    free(m->j_array);
}

void day10(const char* filename){
    const struct problem_inputs day10_lines = read_by_lines(filename);
    size_t m_count = day10_lines.count;
    struct machine m_array[m_count];
    day_parse(m_array, &day10_lines);


    printf("Advent of Code, Day 10\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day10_part1(m_array, m_count);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day10_part2(m_array, m_count);

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

    for (size_t i = 0; i < m_count; i++) {
        free_machine(&m_array[i]);
    }
    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

char* day10_part1(const struct machine* m_array, const size_t m_count){
    for (size_t i = 0; i < m_count; i++) {
        print_machine(&m_array[i]);
    }

    int64_t q = (int64_t)m_count;
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, q);
    return answer;
}

char* day10_part2(const struct machine* m_array, const size_t m_count){
    int64_t q;
    if (m_array == NULL) {
        q = (int64_t)m_count;
    } else {
        q = (int64_t)m_count + 1;
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, q);
    return answer;
}
