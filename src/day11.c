#include "c17_strict.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "ds.h"
#include "io.h"
#include "util.h"
const char* DAY11_PART1_ANSWER = "566";
const char* DAY11_PART2_ANSWER = "331837854931968";


void day11(const char* filename){
    printf("filename: %s\n", filename);
    const struct problem_inputs day11_lines = read_by_lines(filename);

    printf("Advent of Code, Day 11\n");
    if (strcmp(filename, "inputs/2025/day_11_test_02.txt") != 0) {
        printf("    ---------------------------------------------\n");
        printf("\t part 1: ");
        char* answer_part1 = day11_part1(day11_lines);

        printf("\t %s\n", answer_part1);

        if (answer_part1 != NULL && strcmp(answer_part1, DAY11_PART1_ANSWER) != 0) {
            fprintf(stderr, "Day 11, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                    DAY11_PART1_ANSWER, answer_part1);
        }
        if (answer_part1) { free(answer_part1); };
    }
    printf("\t part 2: ");
    char* answer_part2 = day11_part2(day11_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");


    if (answer_part2 != NULL && strcmp(answer_part2, DAY11_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 11, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY11_PART2_ANSWER, answer_part2);
    }


    if (answer_part2) { free(answer_part2); };
}

#define C_SPAN 26
bool seen[C_SPAN][C_SPAN][C_SPAN] = {false};
size_t seen_count = 0;
#define MAX_NODE 586
int64_t cache[MAX_NODE][MAX_NODE];

char int2char(size_t i){
    return (char)((unsigned char)i + 'a');
}

bool mark_seen(const char* str){
    if (seen[str[0] - 'a'][str[1] - 'a'][str[2] - 'a']) {
        return true;
    }
    seen[str[0] - 'a'][str[1] - 'a'][str[2] - 'a'] = true;
    seen_count++;
    return false;
}


// char s[] = "abc";
// size_t idx = pack3_str(s);
static size_t pack_str(const char s[3]){
    return (size_t)(s[0] - 'a') * 26 * 26 +
        (size_t)(s[1] - 'a') * 26 +
        (size_t)(s[2] - 'a') + 1;
}


// char decoded[4];
// unpack3_str(idx, decoded);
static void unpack_str(const size_t id, char out[4]){
    if (id == 0) {
        printf("ERROR: unpack_str called on id==0\n");
        exit(-1);
    }
    size_t x = id - 1;
    out[0] = (char)((x / (26 * 26)) % 26 + 'a');
    out[1] = (char)((x / 26) % 26 + 'a');
    out[2] = (char)(x % 26 + 'a');
    out[3] = '\0';
}

static char unpack_buffer[4];

char* s_unpack(const size_t id){
    if (id == 0) {
        printf("ERROR: unpack_str called on id==0\n");
        exit(-1);
    }
    size_t x = id - 1;
    unpack_buffer[0] = (char)((x / (26 * 26)) % 26 + 'a');
    unpack_buffer[1] = (char)((x / 26) % 26 + 'a');
    unpack_buffer[2] = (char)(x % 26 + 'a');
    unpack_buffer[3] = '\0';
    return unpack_buffer;
}

struct vertex {
    char name[4];
    size_t id;
    size_t n_edges;
    size_t* edges;
};


static void free_vertex(struct vertex* v){
    free(v->edges);
    v->n_edges = 0;
}

#define MAX_ID   (C_SPAN * C_SPAN * C_SPAN + 2)
/*
 *  id(0) is invalid mapping , though id(0) -> |mqp|
 *  valid id range: 1 - 17576
 *
 *  C_SPAN   = 26
 *  C_SPAN^3 = 17576
 *  MAX_ID   = 17577
 *
 *  SIZEMAX: 18446744073709551615
 */

static size_t id_to_index[MAX_ID];
static size_t v_count;
static struct vertex* graph;

static size_t count_paths1(size_t l_id, size_t r_id){
    if (l_id == r_id) { return 1; }
    size_t sum = 0;
    size_t l_idx = id_to_index[l_id];
    for (size_t i = 0; i < graph[l_idx].n_edges; i++) {
        sum += count_paths1(graph[l_idx].edges[i], r_id);
    }
    return sum;
}


size_t count_paths_l(size_t l_id, size_t r_id, size_t level){
    for (size_t j = 0; j < level; j++) {
        printf("\t");
    }
    if (l_id == r_id) {
        size_t idx = id_to_index[l_id];
        printf("match @ %s(%zu,%zu)\n", graph[idx].name, l_id, idx);
        return 1;
    }
    size_t sum = 0;
    size_t l_idx = id_to_index[l_id];
    for (size_t j = 0; j < level; j++) {
        printf("\t");
    }
    printf("%s (id=%zu,idx:%zu) => \n", graph[l_idx].name, l_id, l_idx);
    for (size_t i = 0; i < graph[l_idx].n_edges; i++) {
        sum += count_paths_l(graph[l_idx].edges[i], r_id, level + 1);
    }
    return sum;
}


static void print_vertex(const struct vertex* v){
    char s[4];
    unpack_str(v->id, s);
    printf("v[%s],{%-3s}(id:%zu,idx:%zu)\t [", v->name, s, v->id, id_to_index[v->id]);

    for (size_t i = 0; i < v->n_edges; i++) {
        unpack_str(v->edges[i], s);
        printf("%s(id:%zu,idx:%zu)", s, v->edges[i], id_to_index[v->edges[i]]);
        if (i != v->n_edges - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

char* day11_part1(const struct problem_inputs p_i){
    v_count = p_i.count + 1;

    struct vertex v[v_count];
    memset(&v, 0, sizeof(struct vertex) * v_count);
    for (size_t i = 0; i < p_i.count; i++) {
        const size_t l_len = strlen(p_i.lines[i]);
        struct fstr_vec* pieces = fsplit_on_char(p_i.lines[i], l_len, ' ');

        char parse_buffer[4];
        for (size_t j = 0; j < 3; j++) {
            parse_buffer[j] = pieces->arr[0]->str[j];
        }
        parse_buffer[3] = '\0';
        v[i].id = pack_str(parse_buffer);
        id_to_index[v[i].id] = i;

        const size_t rest_len = pieces->len - 1;
        v[i].n_edges = rest_len;
        v[i].edges = malloc(rest_len * sizeof(size_t));
        for (size_t r = 1; r < pieces->len; r++) {
            v[i].edges[r - 1] = pack_str(pieces->arr[r]->str);
        }
        free_fstr_vec(pieces);
    }
    v[v_count - 1].id = pack_str("out");
    v[v_count - 1].n_edges = 0;
    v[v_count - 1].edges = NULL;
    id_to_index[v[v_count - 1].id] = v_count - 1;


    graph = v;
    size_t path_count = 0;
    size_t you_id = pack_str("you");
    size_t out_id = pack_str("out");

    path_count = count_paths1(you_id, out_id);;
    for (size_t v_i = 0; v_i < v_count; v_i++) {
        free_vertex(&v[v_i]);
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%zu", path_count);
    return answer;
}


static size_t count_paths2(size_t l_id, size_t r_id){
    // printf("count_paths2(%zu, %zu) \n", l_id, r_id);
    if (l_id == r_id) { return 1; }
    size_t l_idx = id_to_index[l_id];
    size_t r_idx = id_to_index[r_id];
    int64_t c = cache[min_st(l_idx, r_idx)][max_st(l_idx, r_idx)];

    if (c != -1) {
        // printf("\t\t hit \t\t %s->%s\n" , s_unpack(l_id), s_unpack(r_id));
        return (size_t)c;
    }

    size_t sum = 0;
    // printf("%s =>\n", s_unpack(l_id));
    for (size_t i = 0; i < graph[l_idx].n_edges; i++) {
        sum += count_paths2(graph[l_idx].edges[i], r_id);
    }

    cache[min_st(l_idx, r_idx)][max_st(l_idx, r_idx)] = (int64_t)sum;
    return sum;
}




size_t count_paths(char* start, char* end){
    size_t l_id = pack_str(start);
    size_t r_id = pack_str(end);
    printf("\t%s -> %s\t ", start, end);
    size_t r = count_paths2(l_id, r_id);
    printf("%zu\n", r);
    return r;
}


void count_paths_b(char* start, char* end, char* req1, char* req2){
}

char* day11_part2(const struct problem_inputs p_i){
    printf("\npart2\n");
    v_count = p_i.count;
    struct vertex v[v_count + 1];
    memset(&v, 0, sizeof(struct vertex) * v_count);
    for (size_t i = 0; i < p_i.count; i++) {
        // printf("parsing line %zu: %s\n", i, p_i.lines[i]);
        const size_t l_len = strlen(p_i.lines[i]);
        struct fstr_vec* pieces = fsplit_on_char(p_i.lines[i], l_len, ' ');

        char parse_buffer[4];
        for (size_t j = 0; j < 3; j++) {
            parse_buffer[j] = pieces->arr[0]->str[j];
        }
        parse_buffer[3] = '\0';
        strcpy(v[i].name, parse_buffer);
        v[i].id = pack_str(parse_buffer);
        id_to_index[v[i].id] = i;

        const size_t rest_len = pieces->len - 1;
        v[i].n_edges = rest_len;
        v[i].edges = malloc(rest_len * sizeof(size_t));
        for (size_t r = 1; r < pieces->len; r++) {
            v[i].edges[r - 1] = pack_str(pieces->arr[r]->str);
        }
        free_fstr_vec(pieces);
    }
    v[v_count - 1].id = pack_str("out");
    v[v_count - 1].n_edges = 0;
    v[v_count - 1].edges = NULL;
    strcpy(v[v_count - 1].name, "out");
    id_to_index[v[v_count - 1].id] = v_count - 1;
    // for (size_t i = 0; i < v_count; i++) {
    //     print_vertex(&v[i]);
    // }
    printf("v_count: %zu\n", v_count);

    graph = v;


    size_t path_count = 0;

    for (size_t i = 0; i < MAX_NODE; i++) {
        for (size_t j = 0; j < MAX_NODE; j++) {
            cache[i][j] = -1;
        }
    }


    count_paths("svr", "out");
    count_paths_b("svr", "out", "dac", "fft");


    // count_paths("svr", "dac");
    // count_paths("dac", "fft");
    // count_paths("fft", "dac");
    // count_paths("fft", "out");
    // count_paths("dac", "out");


    for (size_t v_i = 0; v_i < v_count; v_i++) {
        free_vertex(&v[v_i]);
    }

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%zu", path_count);
    return answer;
}
