#include "c17_strict.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "ds.h"
#include "io.h"
#include "util.h"


const char* DAY10_PART1_ANSWER = "432";
const char* DAY10_PART2_ANSWER = "18011";

static const char LIGHT_ON = '#';
static const char LIGHT_OFF = '.';

struct machine {
    uint64_t goal;
    size_t num_variables;
    size_t num_buttons;
    struct size_vec* b_array;
    size_t* j_array;
    char* input_line;
};

struct entry {
    size_t* pattern; // num_variables length
    size_t min_buttons;
};

struct bucket {
    struct entry* entries;
    size_t count;
    size_t capacity;
};


static inline uint64_t bit_toggle(const uint64_t b, const size_t i){
    return b ^ (uint64_t)(1u << i);
}


static inline uint64_t bit_to_on(const uint64_t b, const size_t i){
    return b | ((uint64_t)1 << i);
}

static inline uint64_t bit_to_off(const uint64_t b, const size_t i){
    return b & ~((uint64_t)1 << i);
}


static uint64_t parse_lights(const fstring* fs){
    uint64_t b = 0;
    size_t b_idx = 0;
    for (size_t i = 1; i < fs->len - 1; i++) {
        if (fs->str[i] == LIGHT_ON) {
            b = bit_to_on(b, b_idx);
        } else if (fs->str[i] == LIGHT_OFF) {
            b = bit_to_off(b, b_idx);
        } else {
            printf("ERROR: unexpected character during parse: %c, expected %c or %c\n",
                   fs->str[i], LIGHT_ON, LIGHT_OFF);
            exit(-1);
        }
        b_idx++;
    }
    return b;
}


static void parse_machine(struct machine* m_array, const struct problem_inputs* p_i){
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

static void free_machine(const struct machine* m){
    for (size_t i = 0; i < m->num_buttons; i++) {
        free_size_vec(&m->b_array[i]);
    }
    free(m->b_array);
    free(m->j_array);
}

static uint64_t apply_presses(const size_t* p, const size_t len, const struct size_vec* w_array){
    uint64_t el = 0;
    for (size_t i = 0; i < len; i++) {
        const struct size_vec* buttons = &w_array[p[i]];
        for (size_t pp = 0; pp < buttons->len; pp++) {
            el = bit_toggle(el, buttons->arr[pp]);
        }
    }
    return el;
}

static bool next_combination(size_t* idx, const size_t k, const size_t n){
    if (k == 0) { return 0; }
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


static void set_parity(const size_t* arr, size_t* p_patt, const size_t size){
    for (size_t i = 0; i < size; i++) {
        p_patt[i] = arr[i] % 2;
    }
}


static void insert_pattern(struct bucket* b, const size_t* pattern, const size_t n_vars, const size_t min_buttons){
    for (size_t i = 0; i < b->count; i++) {
        int same = 1;
        for (size_t j = 0; j < n_vars; j++) {
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
        struct entry* tmp = realloc(b->entries,
                                    b->capacity * sizeof *b->entries);
        if (tmp == NULL) {
            printf("error, %s:%d:realloc failed (old %zu -> new %zu\n",
                   __func__, __LINE__, b->count, b->capacity);
            exit(-1);
        } else {
            b->entries = tmp;
        }
    }

    struct entry* e = &b->entries[b->count++];
    e->pattern = malloc(n_vars * sizeof *e->pattern);
    memcpy(e->pattern, pattern, n_vars * sizeof *pattern);
    e->min_buttons = min_buttons;
}


static struct bucket* patterns(size_t** coeffs, const size_t num_buttons, const size_t num_variables){
    size_t button_range[num_buttons];
    for (size_t i = 0; i < num_buttons; i++) {
        button_range[i] = i;
    }
    const size_t n_patterns = 1u << num_buttons;
    const size_t n_parity = 1u << num_variables;
    struct bucket* buckets = calloc(n_parity, sizeof *buckets);

    size_t* patts[n_patterns];
    size_t* p_patts[n_patterns];

    for (size_t p = 0; p < n_patterns; p++) {
        patts[p] = malloc(num_variables * sizeof(*patts[0]));
        p_patts[p] = malloc(num_variables * sizeof(*p_patts[0]));
        for (size_t k = 0; k < num_variables; k++) {
            patts[p][k] = 0;
            p_patts[p][k] = 0;
        }
    }
    size_t p_idx = 0;
    for (size_t j = 0; j < num_variables; j++) {
        patts[p_idx][j] = 0;
        p_patts[p_idx][j] = 0;
    }
    insert_pattern(&buckets[0], patts[p_idx], num_variables, 0);

    p_idx++;
    for (size_t k = 1; k <= num_buttons; k++) {
        size_t idx[k];
        size_t subset[k];

        for (size_t i = 0; i < k; i++) {
            idx[i] = i;
        }
        while (1) {
            for (size_t i = 0; i < k; i++) {
                subset[i] = button_range[idx[i]];
            }

            for (size_t ss = 0; ss < k; ss++) {
                // ReSharper disable once CppDFANullDereference
                const size_t* coeff_slice = coeffs[subset[ss]];
                for (size_t i = 0; i < num_variables; i++) {
                    patts[p_idx][i] += coeff_slice[i];
                }
            }
            set_parity(patts[p_idx], p_patts[p_idx], num_variables);

            size_t h_idx = 0;
            for (size_t j = 0; j < num_variables; j++) {
                h_idx = (h_idx << 1) | p_patts[p_idx][j];
            }
            insert_pattern(&buckets[h_idx], patts[p_idx], num_variables, k);
            p_idx++;
            if (!next_combination(idx, k, num_buttons)) {
                break;
            }
        }
    }
    for (size_t i = 0; i < n_patterns; i++) {
        free(patts[i]);
        free(p_patts[i]);
    }
    return buckets;
}


static size_t solve_single_aux(struct bucket* buckets, const size_t* goal, const size_t num_variables){
    bool all_zero = true;
    for (size_t i = 0; i < num_variables; i++) {
        if (goal[i] != 0) {
            all_zero = false;
            break;
        }
    }
    if (all_zero) {
        return 0;
    }
    size_t best = 1000000;


    size_t parity_index = 0;
    for (size_t j = 0; j < num_variables; j++) {
        parity_index = (parity_index << 1) | (goal[j] & 1);
    }

    struct bucket* b = &buckets[parity_index];
    for (size_t i = 0; i < b->count; i++) {
        struct entry* e = &b->entries[i];

        bool ok = true;
        for (size_t j = 0; j < num_variables; j++) {
            if (e->pattern[j] > goal[j]) {
                ok = false;
                break;
            }
        }
        if (!ok) { continue; }

        size_t new_goal[num_variables];;
        for (size_t j = 0; j < num_variables; j++)
            new_goal[j] = (goal[j] - e->pattern[j]) / 2;
        size_t cost = e->min_buttons + 2 * solve_single_aux(buckets, new_goal, num_variables);
        if (cost < best) {
            best = cost;
        }
    }
    return best;
}

// static size_t solve_single(size_t** coeffs, const size_t b_num, const size_t v_num, const size_t* goal){
//
//
//     return answer;
// }


void day10(const char* filename){
    const struct problem_inputs day10_lines = read_by_lines(filename);
    const size_t m_count = day10_lines.count;
    struct machine m_array[m_count];
    parse_machine(m_array, &day10_lines);

    printf("Advent of Code, Day 10\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day10_part1(m_array, m_count);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day10_part2(m_array, m_count);
    if (answer_part2 == NULL) {
        printf("part2 answer = NULL\n");
        exit(-1);
    }

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
    // ReSharper disable once CppDFAConstantConditions
    if (answer_part2) { free(answer_part2); };
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
            size_t idx[k];
            size_t subset[k];

            for (size_t i = 0; i < k; i++) {
                idx[i] = i;
            }
            while (1) {
                for (size_t i = 0; i < k; i++) {
                    subset[i] = w_buttons[idx[i]];
                }
                const uint64_t lights = apply_presses(subset, k, m_array[m].b_array);
                if (lights == m_array[m].goal) {
                    sum_of_presses += k;
                    found = true;
                    break;
                }
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


char* day10_part2(const struct machine* m_array, const size_t m_count){
    size_t sum_of_presses = 0;
    for (size_t m = 0; m < m_count; m++) {
        const struct machine* c_machine = &m_array[m];
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

        struct bucket* p_patterns = patterns(coeffs, c_machine->num_buttons, c_machine->num_variables);
        sum_of_presses += solve_single_aux(p_patterns, c_machine->j_array, c_machine->num_variables);


        for (size_t i = 0; i < c_machine->num_buttons; i++) {
            free(coeffs[i]);
        }
        free(coeffs);

        const size_t n_parity = 1u << c_machine->num_variables;
        for (size_t i = 0; i < n_parity; i++) {
            for (size_t j = 0; j < p_patterns[i].count; j++) {
                free(p_patterns[i].entries[j].pattern);
            }
            free(p_patterns[i].entries);
        }
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%zu", sum_of_presses);
    return answer;
}
