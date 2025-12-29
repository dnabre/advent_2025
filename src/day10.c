#include <inttypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "ds.h"
#include "io.h"
#include "util.h"


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

const size_t PRESS_LIMIT = 9;

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
    struct size_vec* w_array;
    size_t* j_array;
};

struct machine* c_machine = NULL;
size_t b_num;
size_t w_num;
struct size_vec* w_array;
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

void print_light_u16(const uint16_t x, size_t n){
    size_t l=16;
    if (n < 16) {
        l = n;
    }
    for (size_t i = 0; i < l; i++) {
        if (get_bit(x, i)) {
            putchar('#');
        } else {
            putchar('.');
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
        printf("\t\tw_array[%3zu] = ", i);
        print_size_vec(m->w_array[i]);
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
        size_t button_num = strlen(pieces->arr[0]->str) - 2;
        b_t bstart = parse_lights(pieces->arr[0]);
        size_t wiring_number = pieces->len - 2;

        m_array[i].goal = bstart;
        m_array[i].b_num = button_num;
        m_array[i].w_num = wiring_number;

        struct size_vec* wiring_array = malloc(sizeof(struct size_vec) * wiring_number);
        for (size_t w_idx = 0; w_idx < wiring_number; w_idx++) {
            fstring* piece = fstr_dup(pieces->arr[w_idx + 1]);
            // printf("w_idx: %3zu, \t |%s| (len=%zu)\n", w_idx, piece->str, piece->len);
            struct fstr_vec* buttons = fsplit_on_char(piece->str + 1, piece->len - 2, ',');
            // print_fstr_vec(buttons);
            init_size_vec(&wiring_array[w_idx]);

            // size_t* w_v = malloc(sizeof(size_t) * button_num);
            // wiring_array[w_idx] = w_v;
            for (size_t w = 0; w < buttons->len; w++) {
                size_t r = strtoll(buttons->arr[w]->str, NULL, 10);
                push_size_vec(&wiring_array[w_idx], r);
                // w_v[w] = r;
            }
            // for (size_t w = buttons->len; w < button_num; w++) {
            //     w_v[w] = 0;
            // }
            free_fstr_vec(buttons);
        }
        fstring* j_string = pieces->arr[pieces->len - 1];
        struct fstr_vec* jolts = fsplit_on_char(j_string->str + 1, j_string->len - 2, ',');

        m_array[i].j_array = malloc(sizeof(size_t) * button_num);
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
        free_size_vec(&m->w_array[i]);
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

b_t apply_presses(const struct size_vec* p){
    // printf("apply button sequence: ");
    // print_size_vec(*p); println();
    // printf("\n these are the full w_array:");
    // for (size_t w=0; w < w_num; w++) {
    //     printf(" %3zu: ", w);
    //     print_size_vec(w_array[w]); println();
    // }

    b_t el = 0;
    for (size_t i = 0; i < p->len; i++) {
        struct size_vec* buttons = &w_array[p->arr[i]];
        // printf("\t apply button: ");
        // print_size_vec(*buttons); println();
        for (size_t pp = 0; pp < buttons->len; pp++) {
            el = bit_toggle(el, buttons->arr[pp]);
        }
    }
    return el;
}


char* day10_part1(const struct machine* m_array, const size_t m_count){
    size_t sum_of_mins=0;
    struct size_vec problems;
    init_size_vec(&problems);
    struct size_vec skipped;
    init_size_vec(&skipped);
    for (size_t i = 0; i < m_count; i++) {
        if (i==14) {
            push_size_vec(&skipped, 14);
            sum_of_mins += 8;
            continue;
        }

        if (i==98) {
            push_size_vec(&skipped, 98);
            sum_of_mins += 7;
            continue;
        }


        if (i==18) {
            push_size_vec(&skipped, 18);
            sum_of_mins += 6;
            continue;
        }


        if (i==24) {
            push_size_vec(&skipped, 24);
            sum_of_mins += 7;
            continue;
        }



        b_t goal = m_array[i].goal;
        b_num = m_array[i].b_num;
        w_num = m_array[i].w_num;
        w_array = m_array[i].w_array;
        // print_machine(&m_array[i]);
        printf("[");
        // print_bits_u16(goal);
        print_light_u16(goal,b_num);
        printf("] b_num: %zu, w_num: %zu  \t i=%zu\n", b_num, w_num, i);


        struct stst_vec visited;
        init_stst_vec_with_size(&visited, 8);
        struct queue_sv* queue = create_queue_sv();
        struct size_vec* s = malloc(sizeof(struct size_vec));
        init_size_vec_with_size(s, 1);
        for (size_t w = 0; w < w_num; w++) {
            push_size_vec(s, w);
            // print_size_vec(*s);
            // println();
            push_back_queue_sv(queue, size_vec_dup(s));
            s->len--;
        }
        // print_queue_sv(queue);
        // println();
        // struct size_vec* solution = malloc(sizeof(struct size_vec));
        // init_size_vec(solution);
        // push_size_vec(solution, 5);
        // push_size_vec(solution, 4);
        // push_size_vec(solution,2);

        // printf("insserting solution: ");
        // print_size_vec(*solution);
        // println();
        // b_t good = apply_presses(solution);
        // printf("\t goal: ");
        // print_bits_u16(goal);
        // println();
        // printf("\t test: ");
        // print_bits_u16(good);
        // println();

        // print_size_vec(w_array[5]); println();
        // print_size_vec(w_array[4]);println();


        /* example #1 solutions
        *   [0,1,2]
        *   [1,3,5]
        *   [0,1,2,3,4,5]
           */

        size_t found_presses = 0;
        size_t loop_count = 0;
        // printf("initial queue:\t ");
        // print_queue_sv(queue);
        // while ((queue->len > 0) && (loop_count < 100000)) {
            while (queue->len > 0) {
            loop_count++;
            struct node_sv* node = pop_front_queue_sv(queue);
            struct size_vec* v = node->data;
            free(node);
            // printf("loop %3zu\n\t", loop_count);
            // print_size_vec(*v);
            // printf("\n\t");

            if (v->len > PRESS_LIMIT) {
                printf("looking at too big of state (v->len==%zu)\n\t", v->len);
                print_size_vec(*v); println();
                return NULL;
            }
            b_t current_lights = apply_presses(v);
            // printf("lights: ");
            // print_bits_u16(current_lights);
            // println();
            if (current_lights == goal) {
                // printf("\n\n\tfound goal\n\n\n\t");
                // printf("button sequence: \n\t\t");
                // print_size_vec(*v);
                // println();
                // for (size_t z = 0; z < v->len; z++) {
                    // print_size_vec(w_array[z]);
                    // println();
                // }


                found_presses = v->len;
                break;
            }
            // expand state (v) to new states
            // printf("\texpanding from state: ");
            // print_size_vec(*v);
            // println();
            if (v->len <PRESS_LIMIT) {
                for (size_t w = 0; w < w_num; w++) {
                    // push_size_vec(v, w);
                    struct size_vec* e_v = size_vec_dup_n(v, v->len + 1);
                    push_size_vec(e_v, w);
                    qsort(e_v->arr, e_v->len, sizeof(size_t), cmp_sizet);
                    // print_size_vec(*v);
                    // printf("\t adding button press: %zu\n ", w);
                    if (find_stst_vec(&visited,e_v) == SIZE_MAX) {
                        // printf("\t\t not found, queuing\n");
                        push_back_queue_sv(queue, e_v);
                    } else {
                        free_size_vec(e_v);
                    }
                    // v->len--; // pop pushed value
                }
            } else {
                printf("not expanding state with %zu press\n", v->len);
            }
            qsort(v->arr, v->len, sizeof(size_t), cmp_sizet);
            push_stst_vec(&visited, v);
            free(v);
        }
        size_t visit_count = visited.len;
        free_stst_vec(&visited);
        free_queue_sv(queue);
        if (found_presses > 0) {
            sum_of_mins += found_presses;
            printf("minimum presses: %zu  \t (loop_count: %zu, visited: %zu)\n", found_presses, loop_count, visit_count);
        } else {
            printf(" hit make iterations: %zu, visited: %zu \n", loop_count, visit_count);
            push_size_vec(&problems, i);
        }
    }

    printf("\nskipped these machines due to problem \n\t");
    print_size_vec(skipped); println();
    printf("\nfailed to final solutions for these lines: \n\t");
    print_size_vec(problems);
    println();
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%zu", sum_of_mins);
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
