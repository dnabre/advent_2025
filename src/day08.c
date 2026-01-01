#include "c17_strict.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "ds.h"
#include "io.h"
#include "parse.h"
#include "util.h"

const char* DAY8_PART1_ANSWER = "96672";
const char* DAY8_PART2_ANSWER = "22517595";


#define DAY_08_SIZE 1000  // size of basically everything
#define PAIRS ((DAY_08_SIZE - 1) * DAY_08_SIZE >> 1) // number of pairs of edges (count {a,b} and {b,a} as one)
#define CIRCUITS N

struct pair {
    int64_t dist;
    size_t p1;
    size_t p2;
};


static size_t edge_count;
static size_t f_scores[DAY_08_SIZE];
static struct size_vec j_circuit[DAY_08_SIZE];


static int compare_edge(const void* p, const void* q){
    const struct pair* a = p;
    const struct pair* b = q;
    if (a->dist < b->dist) return -1;
    if (a->dist > b->dist) return 1;
    return 0;
}


static size_t join_two_edges(const size_t id1, const size_t id2){
    struct size_vec* d = &j_circuit[edge_count];
    push_size_vec(d, id1);
    push_size_vec(d, id2);
    edge_count++;
    f_scores[id1] = edge_count;
    f_scores[id2] = edge_count;
    return d->len;
}


static size_t circuit_union(struct size_vec* je, const size_t id0, const size_t id1){
    size_t src_id, dst_id;
    if (id0 < id1) {
        src_id = id1;
        dst_id = id0;
    } else {
        src_id = id0;
        dst_id = id1;
    }
    struct size_vec* src = &je[src_id - 1];
    struct size_vec* dst = &je[dst_id - 1];
    for (size_t i = 0; i < src->len; i++) {
        push_size_vec(dst, src->arr[i]);
        f_scores[src->arr[i]] = dst_id;
    }
    free(src->arr);
    init_size_vec(src);
    return dst->len;
}

static size_t addpairs(const struct pair* pair, size_t i, const size_t end){
    for (size_t size = 0; i != end && size != DAY_08_SIZE; ++i) {
        const size_t p1 = pair[i].p1;
        const size_t p2 = pair[i].p2;
        const size_t id0 = f_scores[p1];
        const size_t id1 = f_scores[p2];
        if (id0 == 0 && id1 == 0) {
            size = join_two_edges(p1, p2);
        } else if ((id0 == 0) || (id1 == 0)) {
            size_t id;
            size_t point;
            if (id0 == 0) {
                id = id1;
                point = p1;
            } else {
                id = id0;
                point = p2;
            }
            push_size_vec(&j_circuit[id - 1], point);
            f_scores[point] = id;
            size = j_circuit[id - 1].len;
        } else if (id0 != id1) {
            size = circuit_union(j_circuit, id0, id1);
        }
    }
    return i - 1;
}


struct pair* day8_parse_and_sort(struct point3 junctionbox[]){
    struct pair* pairs = malloc(sizeof(struct pair) * PAIRS);
    if (!pairs) {
        printf("malloc error\n");
        exit(-1);
    }
    for (int i = 0, m = 0; i < DAY_08_SIZE - 1; ++i) {
        for (int j = i + 1; j < DAY_08_SIZE; ++j) {
            pairs[m] = (struct pair){calc_distance(junctionbox[i], junctionbox[j]), i, j};
            m++;
        }
    }
    qsort(pairs, PAIRS, sizeof(struct pair), compare_edge);
    return pairs;
}


void day8(const char* filename){
    struct point3 junctionbox[DAY_08_SIZE];
    struct problem_inputs day8_lines = read_by_lines(filename);
    for (size_t i = 0; (i < day8_lines.count) && (i < DAY_08_SIZE); i++) {
        junctionbox[i] = parse_3d_point_from_line(day8_lines.lines[i]);
    }
    struct pair* pairs = day8_parse_and_sort(junctionbox);
    printf("Advent of Code, Day 08\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day8_part1(pairs);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day8_part2(pairs, junctionbox);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY8_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 8, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY8_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY8_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 8, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY8_PART2_ANSWER, answer_part2);
    }

    free(pairs);
    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

char* day8_part1(const struct pair* pairs){
    addpairs(pairs, 0, DAY_08_SIZE);
    size_t circuit_size[DAY_08_SIZE];
    size_t k = 0;
    for (size_t i = 0; i < edge_count; ++i) {
        if (j_circuit[i].len > 1) {
            circuit_size[k++] = j_circuit[i].len;
        }
    }
    qsort(circuit_size, k, sizeof *circuit_size, size_t_compare_r);
    const size_t product = circuit_size[0] * circuit_size[1] * circuit_size[2];

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%zu", product);
    return answer;
}

char* day8_part2(const struct pair* pairs, const struct point3* jb){
    const size_t a2_i = addpairs(pairs, DAY_08_SIZE, PAIRS);
    const int64_t answer2 = jb[pairs[a2_i].p1].x * jb[pairs[a2_i].p2].x;

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, answer2);
    return answer;
}
