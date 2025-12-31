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
    size_t num_variables;
    size_t num_buttons;
    struct size_vec* b_array;
    size_t* j_array;
    char* input_line;
};


static const char LIGHT_ON = '#';
// static const char LIGHT_OFF = '.';

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


// static void print_light_u16(const uint16_t x, const size_t n){
//     size_t l = 16;
//     if (n < 16) {
//         l = n;
//     }
//     for (size_t i = 0; i < l; i++) {
//         if (get_bit(x, i)) {
//             putchar(LIGHT_ON);
//         } else {
//             putchar(LIGHT_OFF);
//         }
//     }
// }


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
    printf("\t v_num : %zu\n", m->num_variables);
    printf("\t b_num : %zu\n", m->num_buttons);
    printf("\t buttons:\n");
    for (size_t i = 0; i < m->num_buttons; i++) {
        printf("\t\tb_array[%3zu] = ", i);
        print_size_vec(m->b_array[i]);
        println();
    }
    printf("\t jolts : ");
    print_size_t_array(m->j_array, m->num_variables);
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
        m_array[i].num_variables = button_num;
        m_array[i].num_buttons = wiring_number;
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
        m_array[i].b_array = wiring_array;
    }
}

void free_machine(const struct machine* m){
    for (size_t i = 0; i < m->num_buttons; i++) {
        free_size_vec(&m->b_array[i]);
    }
    free(m->b_array);
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
        const size_t which_button = p->arr[i];
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


void set_parity(size_t* arr, size_t* p_patt, size_t size){
    for (size_t i = 0; i < size; i++) {
        p_patt[i] = arr[i] % 2;
    }
}
struct entry {
    size_t* pattern;       // num_variables length
    size_t min_buttons;
};

struct bucket {
    struct entry *entries;
    size_t count;
    size_t capacity;
};

void insert_pattern(struct bucket *b,
                    size_t *pattern,
                    size_t num_variables,
                    size_t min_buttons)
{
    for (size_t i = 0; i < b->count; i++) {
        int same = 1;
        for (size_t j = 0; j < num_variables; j++) {
            if (b->entries[i].pattern[j] != pattern[j]) {
                same = 0;
                break;
            }
        }
        if (same)
            return; // already stored with minimal button count
    }

    if (b->count == b->capacity) {
        b->capacity = b->capacity ? b->capacity * 2 : 4;
        b->entries = realloc(b->entries,
                             b->capacity * sizeof *b->entries);
    }

    struct entry *e = &b->entries[b->count++];
    e->pattern = malloc(num_variables * sizeof *e->pattern);
    memcpy(e->pattern, pattern, num_variables * sizeof *pattern);
    e->min_buttons = min_buttons;
}


struct out {
    struct bucket *buckets;
    size_t** patts;
    size_t** p_patts;
    size_t num_variables;
    size_t b_num;


};


struct out patterns(size_t** coeffs, size_t num_buttons, size_t num_variables){
    printf("patterns\n");


    size_t button_range[num_buttons];
    for (size_t i = 0; i < num_buttons; i++) {
        button_range[i] = i;
    }
    // printf("button range: \t"); print_size_t_array(button_range, b_num); println();

    const size_t n_parity = 1u << num_variables;
    struct bucket *buckets = calloc(n_parity, sizeof *buckets);


    // compute bucket index
    // size_t bucket = 0;
    // for (size_t j = 0; j < num_variables; j++)
    //     bucket = (bucket << 1) | p_patts[k][j];



    const size_t n_patterns = 1u << num_buttons;
    // size_t patts[n_patterns][num_variables];
    // size_t p_patts[n_patterns][num_variables];
    size_t** patts = malloc(n_patterns * sizeof(*patts));
    size_t** p_patts = malloc(n_patterns * sizeof(*p_patts));


    for (size_t p = 0; p < n_patterns; p++) {
        patts[p] = malloc(num_variables * sizeof(*patts[0]));
        p_patts[p] = malloc(num_variables * sizeof(*p_patts[0]));
        for (size_t k = 0; k < num_variables; k++) {
            patts[p][k] = 0;
            p_patts[p][k] = 0;
        }
    }
    size_t p_idx =0;
    // printf("%zu: ", p_idx);
    // print_size_t_array(patts[p_idx], num_variables);
    // println();
    // set_parity(patts[p_idx],p_patts[p_idx], num_variables );
    for (size_t j = 0; j < num_variables; j++)
        patts[p_idx][j] = 0;

    for (size_t j = 0; j < num_variables; j++)
        p_patts[p_idx][j] = 0;

    insert_pattern(&buckets[0], patts[p_idx], num_variables, 0);




    p_idx++;


    for (size_t k = 1; k <= num_buttons; k++) {
        size_t idx[k]; // indices
        size_t subset[k]; // values

        // setup first combination
        for (size_t i = 0; i < k; i++) {
            idx[i] = i;
        }

        while (1) {
            // build the actual subset values
            for (size_t i = 0; i < k; i++) {
                subset[i] = button_range[idx[i]];
            }

            for (size_t ss = 0; ss < k; ss++) {
                const size_t* coeff_slice = coeffs[subset[ss]];
                for (size_t i = 0; i < num_variables; i++) {
                    patts[p_idx][i] += coeff_slice[i];
                }
            }
            // printf("%zu: ", p_idx); print_size_t_array(patts[p_idx], num_variables);
            // printf("\t subset: "); print_size_t_array(subset, k);
            // printf("\t k=%zu", k);
            // println();

            // printf("\t par: "); print_size_t_array(p_patts[p_idx], num_variables); println();


            set_parity(patts[p_idx],p_patts[p_idx], num_variables );


            size_t h_idx =0;
            for (size_t j=0; j < num_variables; j++) {
                h_idx = (h_idx << 1) | p_patts[p_idx][j];
            }

            insert_pattern(&buckets[h_idx],
                   patts[p_idx],
                   num_variables,
                   k);



            p_idx++;
            // next combination
            if (!next_combination(idx, k, num_buttons)) {
                break;
            }
        }
    }
    printf("------------------\n");


    struct out r_out = {buckets, patts, p_patts, num_variables, num_buttons};
    // for (size_t p = 0; p < n_parity; p++) {
        // struct bucket *b = &buckets[p];

        // printf("Bucket %zu (count=%zu):\n", p, b->count);
        //
        // for (size_t i = 0; i < b->count; i++) {
        //     struct entry *e = &b->entries[i];
        //
        //     printf("  pattern: ");
        //     for (size_t j = 0; j < num_variables; j++)
        //         printf("%zu ", e->pattern[j]);
        //
        //     printf("  cost=%zu\n", e->min_buttons);
        // }
    // }





    return r_out;
}





char* day10_part1(const struct machine* m_array, const size_t m_count){
    size_t max_wiring_num = 0;
    for (size_t i = 0; i < m_count; i++) {
        max_wiring_num = max_st(max_wiring_num, m_array[i].num_buttons);
    }
    size_t w_buttons[max_wiring_num];
    for (size_t i = 0; i < max_wiring_num; i++) {
        w_buttons[i] = i;
    }

    size_t sum_of_presses = 0;
    for (size_t m = 0; m < m_count; m++) {
        bool found = false;
        for (size_t k = 1; k <= m_array[m].num_buttons; k++) {
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
                const uint64_t lights = apply_presses(subset, k, m_array[m].b_array);
                if (lights == m_array[m].goal) {
                    sum_of_presses += k;
                    found = true; // for checking if for-loop should break
                    break; // break out of while loop
                }
                // next combination
                if (!next_combination(idx, k, m_array[m].num_buttons))
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
    const struct machine machine = *mach;

    size_t w_buttons[machine.num_buttons];
    for (size_t i = 0; i < machine.num_buttons; i++) {
        w_buttons[i] = i;
    }
    for (size_t k = 1; k <= machine.num_buttons; k++) {
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


            const uint64_t lights = apply_presses(subset, k, machine.b_array);
            if (lights == machine.goal) {
                for (size_t i = 0; i < k; i++) {
                    print_size_vec(machine.b_array[subset[i]]);
                    printf(" ");
                }


                printf("\t good\n");
            }


            // next combination
            if (!next_combination(idx, k, machine.num_buttons)) {
                break;
            }
        }
    }

    return NULL;
}
size_t base_case_count=0;
size_t solve_single_aux(const size_t *goal,
    size_t num_variables, struct bucket* buckets) {

    // printf("ssa goal: "); print_size_t_array(goal, num_variables); println();
    // printf("num_variables: %zu\n", num_variables);
    bool all_zero = true;
    for (size_t i = 0; i < num_variables; i++) {
        if (goal[i] != 0) {
            all_zero = false;
            break;
        }
    }
    if (all_zero) {
        base_case_count++;
        // printf("\t\t base case hit (time=%zu)\n\n", base_case_count);
        return 0;
    }
    size_t best = 1000000;

    // compute parity index
    size_t parity_index = 0;
    for (size_t j = 0; j < num_variables; j++)
        parity_index = (parity_index << 1) | (goal[j] & 1);

    // --- ADD THIS ---
    // printf("C parity tuple: ");
    // for (int bit = num_variables - 1; bit >= 0; bit--)
    //     printf("%zu ", (parity_index >> bit) & 1);
    // printf("\n");
    //
    // printf("C bucket:\n");
    // for (size_t i = 0; i < buckets[parity_index].count; i++) {
    //     struct entry *e = &buckets[parity_index].entries[i];
    //     printf("  pattern: ");
    //     for (size_t j = 0; j < num_variables; j++)
    //         printf("%zu ", e->pattern[j]);
    //     printf(" cost=%zu\n", e->min_buttons);
    // }

    struct bucket *b = &buckets[parity_index];
    // printf("b->count: %zu\n", b->count);
    // iterate over patterns in this bucket
    for (size_t i = 0; i < b->count; i++) {
        struct entry *e = &b->entries[i];

        // feasibility check
        int ok = 1;
        for (size_t j = 0; j < num_variables; j++) {
            if (e->pattern[j] > goal[j]) {
                ok = 0;
                break;
            }
        }
        if (!ok) continue;
        // printf("pattern: ");
        // print_size_t_array(e->pattern, num_variables); println();
        // printf("pattern_cost: %zu\n", e->min_buttons);


        // compute new_goal
        // size_t new_goal[num_variables];
        size_t* new_goal = malloc(num_variables * sizeof(size_t));
        for (size_t j = 0; j < num_variables; j++)
            new_goal[j] = (goal[j] - e->pattern[j]) / 2;
        // printf("new_goal: ");print_size_t_array(new_goal, num_variables); println();
        // recurse
        size_t cost = e->min_buttons + 2 * solve_single_aux(new_goal,
                                                            num_variables,
                                                            buckets);
        free(new_goal);
        if (cost < best) {

            best = cost;
        }
    }




    return best;
}
size_t solve_single(size_t** coeffs, size_t b_num, size_t v_num, size_t* goal){
    printf("solve_single\n");
    struct out   output = patterns(coeffs, b_num, v_num);
    printf("num_variables: %zu\n", v_num);
    printf("b_num: %zu\n", b_num);
    // size_t answer= solve_single_aux(goal,&output);
    size_t answer = solve_single_aux(goal, output.num_variables, output.buckets);

    return answer;
}

// highest entry in jolt list is 277
char* day10_part2(struct machine* m_array, const size_t m_count){
    println();
     size_t sum_of_presses = 0;

    size_t max_num_buttons =0;
    size_t max_num_variables =0;

     for (size_t m=0; m < m_count; m++)
    {
        const struct machine* c_machine = &m_array[m];
        // print_machine(c_machine);

        max_num_buttons = max_st(max_num_buttons, c_machine->num_buttons);
        max_num_variables = max_st(max_num_variables, c_machine->num_variables);
        size_t** coeffs = malloc(sizeof(size_t*) * c_machine->num_buttons);
        for (size_t i = 0; i < c_machine->num_buttons; i++) {
            coeffs[i] = malloc(sizeof(size_t) * c_machine->num_variables);
            const struct size_vec* buttons = &c_machine->b_array[i];
            for (size_t j = 0; j < c_machine->num_variables; j++) {
                coeffs[i][j] = 0;
            }
            for (size_t j = 0; j < buttons->len; j++) {
                const size_t b_idx = buttons->arr[j];
                coeffs[i][b_idx] = 1;
            }
        }
        printf("goal:\n\t");
        print_size_t_array(c_machine->j_array, c_machine->num_variables);
        println();
        size_t subscore = solve_single(coeffs, c_machine->num_buttons, c_machine->num_variables,
                                       c_machine->j_array);
        sum_of_presses += subscore;
        printf("\t\t\t\t\tsubscore: %zu\n", subscore);
        // printf("coeffs\n");
        // for (size_t i = 0; i < c_machine->b_num; i++) {
        //     for (size_t j = 0; j < c_machine->v_num; j++) {
        //         printf("%zu ", coeffs[i][j]);
        //     }
        //     println();
        // }

        for (size_t i = 0; i < c_machine->num_buttons; i++) {
            free(coeffs[i]);
        }
        free(coeffs);
    }

    printf("sum_of_presses: %zu\n", sum_of_presses);
    printf("day10_part2: done\n");
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%zu", sum_of_presses);
    return answer;
}
