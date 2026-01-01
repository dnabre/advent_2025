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
    const struct problem_inputs day11_lines = read_by_lines(filename);

    printf("Advent of Code, Day 11\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day11_part1(day11_lines);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day11_part2(day11_lines);

    printf("\t %s\n", answer_part2);
    printf("    ---------------------------------------------\n");

    if (strcmp(answer_part1, DAY11_PART1_ANSWER) != 0) {
        fprintf(stderr, "Day 11, Part 1, answer is WRONG. Expected: %s, Received: %s\n",
                DAY11_PART1_ANSWER, answer_part1);
    }
    if (strcmp(answer_part2, DAY11_PART2_ANSWER) != 0) {
        fprintf(stderr, "Day 11, Part 2, answer is WRONG. Expected: %s, Received: %s\n",
                DAY11_PART2_ANSWER, answer_part2);
    }


    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

#define C_SPAN 26
bool seen[C_SPAN][C_SPAN][C_SPAN] = {false};
size_t seen_count = 0;

static char int2char(size_t i){
    return (char)((unsigned char)i + 'a');
}

static bool mark_seen(const char* str){
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

static char* s_unpack(const size_t id){
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
    size_t id;
    size_t n_edges;
    size_t* edges;
};

static void print_vertex(const struct vertex* v){
    char s[4];
    unpack_str(v->id, s);
    printf("v=: %5s, [", s);

    for (size_t i = 0; i < v->n_edges; i++) {
        unpack_str(v->edges[i], s);
        printf("%s", s);
        if (i != v->n_edges - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
static void free_vertex(struct vertex* v){
    free(v->edges);
    v->n_edges = 0;
}
#define MAX_ID   (C_SPAN * C_SPAN * C_SPAN + 1)
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

static size_t count_paths(size_t l_id, size_t r_id){
    if (l_id == r_id) { return 1; }
    size_t sum =0;
    size_t l_idx = id_to_index[l_id];
    for (size_t i = 0; i < graph[l_idx].n_edges; i++) {
        sum += count_paths(graph[l_idx].edges[i], r_id);
    }
    return sum;
}

char* day11_part1(const struct problem_inputs p_i){

     v_count = p_i.count;
    struct vertex v[v_count];


    for (size_t i = 0; i < p_i.count; i++) {
        const size_t l_len = strlen(p_i.lines[i]);
        struct fstr_vec* pieces = fsplit_on_char(p_i.lines[i], l_len, ' ');
        // printf("%3zu: parsed line length: %zu, contents: |%s|\n",i, pieces->len, p_i.lines[i]);
        // printf("\t%zu parts: \n", pieces->len);

        char parse_buffer[4];
        for (size_t j = 0; j < 3; j++) {
            parse_buffer[j] = pieces->arr[0]->str[j];
        }
        parse_buffer[3] = '\0';

        v[i].id = pack_str(parse_buffer);
        id_to_index[v[i].id] = i;
        // printf("\tfirst: |%s|, id=%zu, idx=%zu, id_to_index[%zu]=%zu]\n", parse_buffer,v[i].id, i, v[i].id, id_to_index[v[i].id]);


        const size_t rest_len = pieces->len - 1;
        v[i].n_edges = rest_len;
        v[i].edges = malloc(rest_len * sizeof(size_t));
        // printf("\n\trest of string has %zu pieces\n", rest_len);
        for (size_t r = 1; r < pieces->len; r++) {
            // printf("\t\t%zu: %-8s\t packed: %zu\n", r, pieces->arr[r]->str, pack_str(pieces->arr[r]->str));
            v[i].edges[r - 1] = pack_str(pieces->arr[r]->str);
        }
        // print_vertex(&v[i]);
        // println();
        free_fstr_vec(pieces);
    }


    graph = v;
    size_t path_count1=0;
    // size_t you_id = pack_str("you");
    // size_t out_id1 = pack_str("out");
    // path_count= count_paths(you_id, out_id1);

    println();
    size_t srv_id = pack_str("srv"); printf("srv_id: %zu\n", srv_id);
    size_t out_id = pack_str("out"); printf("out_id: %zu\n", out_id);
    size_t dac_id = pack_str("dac");printf("dac_id: %zu\n", dac_id);
    size_t fft_id = pack_str("fft");printf("fft_id: %zu\n", fft_id);
    size_t path_count = 0;

    // size_t s_d = count_paths(srv_id, out_id);printf("srv => dac: %zu\n", s_d);
// printf("s_d: %zu\n", s_d);


    // size_t s_d = count_paths(srv_id, dac_id);printf("srv => dac: %zu\n", s_d);
    // size_t s_f = count_paths(srv_id, fft_id);printf("srv => fft: %zu\n", s_f);
    // size_t d_o = count_paths(dac_id, out_id);  printf("dac => out: %zu\n", d_o);
    // size_t f_o = count_paths(fft_id, out_id);printf("fft => out: %zu\n", f_o);
    // size_t d_f = count_paths(dac_id, fft_id);printf("dac => fft: %zu\n", d_f);
    // size_t f_d = count_paths(fft_id, dac_id);printf("fft => dac: %zu\n", f_d);
    println();







    // for (size_t v_i=0; v_i < v_count; v_i++) {
    //     free_vertex(&v[v_i]);
    // }


    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%zu", path_count1);
    return answer;
}

char* day11_part2(const struct problem_inputs p_i){
    println();
    printf("day2");
    // v_count = p_i.count;
    // struct vertex v[v_count];
    //
    //
    // for (size_t i = 0; i < p_i.count; i++) {
    //     const size_t l_len = strlen(p_i.lines[i]);
    //     struct fstr_vec* pieces = fsplit_on_char(p_i.lines[i], l_len, ' ');
    //     // printf("%3zu: parsed line length: %zu, contents: |%s|\n",i, pieces->len, p_i.lines[i]);
    //     // printf("\t%zu parts: \n", pieces->len);
    //
    //     char parse_buffer[4];
    //     for (size_t j = 0; j < 3; j++) {
    //         parse_buffer[j] = pieces->arr[0]->str[j];
    //     }
    //     parse_buffer[3] = '\0';
    //
    //     v[i].id = pack_str(parse_buffer);
    //     id_to_index[v[i].id] = i;
    //     // printf("\tfirst: |%s|, id=%zu, idx=%zu, id_to_index[%zu]=%zu]\n", parse_buffer,v[i].id, i, v[i].id, id_to_index[v[i].id]);
    //
    //
    //     const size_t rest_len = pieces->len - 1;
    //     v[i].n_edges = rest_len;
    //     v[i].edges = malloc(rest_len * sizeof(size_t));
    //     // printf("\n\trest of string has %zu pieces\n", rest_len);
    //     for (size_t r = 1; r < pieces->len; r++) {
    //         // printf("\t\t%zu: %-8s\t packed: %zu\n", r, pieces->arr[r]->str, pack_str(pieces->arr[r]->str));
    //         v[i].edges[r - 1] = pack_str(pieces->arr[r]->str);
    //     }
    //     // print_vertex(&v[i]);
    //     // println();
    //     free_fstr_vec(pieces);
    // }

    println();

    // graph = v;




size_t path_count =0;

    // for (size_t v_i=0; v_i < v_count; v_i++) {
    //     free_vertex(&v[v_i]);
    // }
    printf("\n---------- day11 part2 done------------------\n");

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%zu", path_count);
    return answer;
}
