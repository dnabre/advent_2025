#include <inttypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "ds.h"
#include "io.h"
#include "util.h"


const char* DAY10_PART1_ANSWER = "432";
const char* DAY10_PART2_ANSWER = "18011";

struct machine {
    uint64_t goal;
    size_t b_num;
    size_t w_num;
    struct size_vec* w_array;
    size_t* j_array;
    char* input_line;
};


static const char LIGHT_ON = '#';
static const char LIGHT_OFF = '.';

static inline uint64_t bit_toggle(const uint64_t b, const size_t i){
    return b ^ (uint64_t)(1u << i);
}

static inline bool get_bit(const uint64_t b, const size_t i){
    return (b >> i) & 1u;
}


static inline uint64_t bit_to_on(const uint64_t b, const size_t i){
    return b | ((uint64_t)1 << i);
}

static inline uint64_t bit_to_off(const uint64_t b, const size_t i){
    return b & ~((uint64_t)1 << i);
}


static void print_light_u16(const uint16_t x, const size_t n){
    size_t l = 16;
    if (n < 16) {
        l = n;
    }
    for (size_t i = 0; i < l; i++) {
        if (get_bit(x, i)) {
            putchar(LIGHT_ON);
        } else {
            putchar(LIGHT_OFF);
        }
    }
}


static uint64_t parse_lights(const fstring* fs){
    uint64_t b = 0;
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

static void print_bt(const uint64_t b, const size_t n){
    for (size_t i = 0; i < n; i++) {
        if (get_bit(b, i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
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
    printf("%s\n", m->input_line);
    printf("\n-----------------------------------------\n");
}


void parse_machine(struct machine* m_array, const struct problem_inputs* p_i){
    for (size_t i = 0; i < p_i->count; i++) {
        const char* ln = p_i->lines[i];
        const size_t len = strlen(ln);
        m_array[i].goal = 0;

        struct fstr_vec* pieces = fsplit_on_char(ln, len, ' ');
        const size_t button_num = strlen(pieces->arr[0]->str) - 2;
        const uint64_t bstart = parse_lights(pieces->arr[0]);
        const size_t wiring_number = pieces->len - 2;

        m_array[i].goal = bstart;
        m_array[i].b_num = button_num;
        m_array[i].w_num = wiring_number;
        m_array[i].input_line = p_i->lines[i];
        struct size_vec* wiring_array = malloc(sizeof(struct size_vec) * wiring_number);
        for (size_t w_idx = 0; w_idx < wiring_number; w_idx++) {
            const fstring* piece = fstr_dup(pieces->arr[w_idx + 1]);
            struct fstr_vec* buttons = fsplit_on_char(piece->str + 1, piece->len - 2, ',');
            init_size_vec(&wiring_array[w_idx]);
            for (size_t w = 0; w < buttons->len; w++) {
                const size_t r = strtoll(buttons->arr[w]->str, NULL, 10);
                push_size_vec(&wiring_array[w_idx], r);
            }
            free_fstr_vec(buttons);
        }
        const fstring* j_string = pieces->arr[pieces->len - 1];
        struct fstr_vec* jolts = fsplit_on_char(j_string->str + 1, j_string->len - 2, ',');

        m_array[i].j_array = malloc(sizeof(size_t) * button_num);
        for (size_t j = 0; j < jolts->len; j++) {
            const size_t jj = strtoll(jolts->arr[j]->str, NULL, 10);
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

static bool next_combination(size_t* idx, const size_t k, const size_t n){
    if (k == 0) return 0;

    size_t i = k - 1;
    while (1) {
        if (idx[i] < (n - (k - i))) {
            idx[i]++;
            for (size_t j = i + 1; j < k; j++) {
                idx[j] = idx[j - 1] + 1;
            }
            return true;
        }
        if (i == 0) {
            return false;
        }
        i--;
    }
}

void day10(const char* filename){
    const struct problem_inputs day10_lines = read_by_lines(filename);
    const size_t m_count = day10_lines.count;
    struct machine m_array[m_count];
    parse_machine(m_array, &day10_lines);

    char* answer_part1 = NULL;
    char* answer_part2 = NULL;
    printf("Advent of Code, Day 10\n");
    printf("    ---------------------------------------------\n");
    // printf("\t part 1: ");
    //  answer_part1 = day10_part1(m_array, m_count);
    //
    // printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    answer_part2 = day10_part2(m_array, m_count);
    if (answer_part2 == NULL) {
        printf("part2 answer = NULL\n");
        exit(-1);
    }

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    // if (strcmp(answer_part1, DAY10_PART1_ANSWER) != 0) {
    //     fprintf(stderr, "Day 10, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
    //             DAY10_PART1_ANSWER, answer_part1);
    // }
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

uint64_t apply_presses(const size_t* p, const size_t len, struct size_vec* w_array){
    uint64_t el = 0;
    for (size_t i = 0; i < len; i++) {
        const struct size_vec* buttons = &w_array[p[i]];
        // printf("\t apply button: ");
        // print_size_vec(*buttons); println();
        for (size_t pp = 0; pp < buttons->len; pp++) {
            el = bit_toggle(el, buttons->arr[pp]);
        }
    }
    return el;
}

size_t* apply_j_presses(struct size_vec* p, const size_t b_num, struct size_vec* w_array){
    printf("button press (%zu total):\n\t", p->len);
    print_size_vec(*p);
    println();

    size_t* j_values = malloc(sizeof(size_t) * b_num);
    for (size_t i = 0; i < b_num; i++) {
        j_values[i] = 0;
    }
    printf("initial jolt array:\n\t");
    print_size_t_array(j_values, b_num);
    println();
    println();

    for (size_t i = 0; i < p->len; i++) {
        size_t which_button = p->arr[i];
        printf("press button %zu", which_button);
        const struct size_vec* buttons = &w_array[which_button];
        printf("\t apply button: ");
        print_size_vec(*buttons);
        println();
        for (size_t pp = 0; pp < buttons->len; pp++) {
            j_values[buttons->arr[pp]]++;
        }
        print_size_t_array(j_values, b_num);
        println();
    }
    // return el;
    return j_values;
}


char* day10_part1(const struct machine* m_array, const size_t m_count){
    size_t max_wiring_num = 0;
    for (size_t i = 0; i < m_count; i++) {
        max_wiring_num = max_st(max_wiring_num, m_array[i].w_num);
    }
    size_t w_buttons[max_wiring_num];
    for (size_t i = 0; i < max_wiring_num; i++) {
        w_buttons[i] = i;
    }

    size_t sum_of_presses = 0;
    for (size_t m = 0; m < m_count; m++) {
        bool found = false;
        for (size_t k = 1; k <= m_array[m].w_num; k++) {
            size_t idx[k]; // indices
            size_t subset[k]; // values

            // setup first combination
            for (size_t i = 0; i < k; i++) {
                idx[i] = i;
            }
            while (1) {
                // build the actual subset values
                for (size_t i = 0; i < k; i++) {
                    subset[i] = w_buttons[idx[i]];
                }
                const uint64_t lights = apply_presses(subset, k, m_array[m].w_array);
                if (lights == m_array[m].goal) {
                    sum_of_presses += k;
                    found = true; // for checking if for-loop should break
                    break; // break out of while loop
                }
                // next combination
                if (!next_combination(idx, k, m_array[m].w_num))
                    break;
            }
            if (found) {
                break;
            }
        }
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%zu", sum_of_presses);
    return answer;
}

struct size_vec* p1(const struct machine* mach){
    struct machine machine = *mach;

    size_t w_buttons[machine.w_num];
    for (size_t i = 0; i < machine.w_num; i++) {
        w_buttons[i] = i;
    }
    for (size_t k = 1; k <= machine.w_num; k++) {
        size_t idx[k]; // indices
        size_t subset[k]; // values

        // setup first combination
        for (size_t i = 0; i < k; i++) {
            idx[i] = i;
        }
        while (1) {
            // build the actual subset values
            for (size_t i = 0; i < k; i++) {
                subset[i] = w_buttons[idx[i]];
            }



            const uint64_t lights = apply_presses(subset, k, machine.w_array);
            if (lights == machine.goal) {
                for (size_t i = 0; i < k; i++) {
                    print_size_vec(machine.w_array[subset[i]]);
                    printf(" ");
                }



                printf("\t good\n");
            }

            // printf("pressing: ");
            // for (size_t i = 0; i < k; i++) {
            //     print_size_vec(machine.w_array[ subset[i]]);
            //     printf(" ");
            // }
            // printf("\t.\n");
            // break;
            // return r;
            // next combination
            if (!next_combination(idx, k, machine.w_num)) {

                break;
            }
        }
    }

    return NULL;
}


size_t solve_single_aux(size_t* goal, size_t goal_len){
    bool all_zero = true;
    for (size_t i=0; i < goal_len; i++) {
        if (goal[i] !=0) {
            all_zero = false;
            break;
        }
    }
    if (all_zero) {
        return 0;
    }
    size_t answer = 1000000;
    return answer;

}





// highest entry in jolt list is 277
char* day10_part2(const struct machine* m_array, const size_t m_count){
    // size_t max_wiring_num = 0;
    // for (size_t i = 0; i < m_count; i++) {
    //     max_wiring_num = max_st(max_wiring_num, m_array[i].w_num);
    // }
    // size_t w_buttons[max_wiring_num];
    // for (size_t i = 0; i < max_wiring_num; i++) {
    //     w_buttons[i] = i;
    // }


    size_t sum_of_presses = 0;
    // for (size_t m = 0; m < m_count; m++)
    size_t m = 0;
    {
        print_machine(&m_array[m]);
        struct size_vec* p1_sol = p1(&m_array[m]);
        if (p1_sol == NULL) {
            printf("p1_sol finished, but returned NULL\n");
            return NULL;
        }
        print_size_vec(*p1_sol);
        println();
        size_t* j = apply_j_presses(p1_sol, m_array[m].b_num, m_array[m].w_array); // return is length b_num
        if (j) {
            print_size_t_array(j, m_array[m].b_num);
            println();
            printf("\n\n");
        }
        // struct size_vec good_press;
        // init_size_vec_with_size(&good_press,10);
        // push_size_vec(&good_press, 0);
        //
        // push_size_vec(&good_press, 1);
        // push_size_vec(&good_press, 1);
        // push_size_vec(&good_press, 1);
        //
        // push_size_vec(&good_press, 3);
        // push_size_vec(&good_press, 3);
        // push_size_vec(&good_press, 3);
        //
        // push_size_vec(&good_press, 4);
        //
        // push_size_vec(&good_press, 5);
        // push_size_vec(&good_press, 5);
        // size_t* j2 = apply_j_presses(&good_press,m_array[m].b_num,m_array[m].w_array);
        // print_size_t_array(j2, m_array[m].b_num);println();


        sum_of_presses += p1_sol->len;
        // bool found = false;
        // for (size_t k = 1; k <= m_array[m].w_num; k++) {
        //     size_t idx[k]; // indices
        //     size_t subset[k]; // values
        //
        //     // setup first combination
        //     for (size_t i = 0; i < k; i++) {
        //         idx[i] = i;
        //     }
        //     while (1) {
        //         // build the actual subset values
        //         for (size_t i = 0; i < k; i++) {
        //             subset[i] = w_buttons[idx[i]];
        //         }
        //         const uint64_t lights = apply_presses(subset, k, m_array[m].w_array);
        //         if (lights == m_array[m].goal) {
        //             sum_of_presses += k;
        //             found = true;  // for checking if for-loop should break
        //             break;         // break out of while loop
        //         }
        //         // next combination
        //         if (!next_combination(idx, k, m_array[m].w_num))
        //             break;
        //     }
        //     if (found) {
        //         break;
        //     }
        // }
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%zu", sum_of_presses);
    return answer;
}
