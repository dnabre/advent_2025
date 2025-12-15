#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "days.h"
#include "ds.h"
#include "io.h"
#include "parse.h"
const char* DAY8_PART1_ANSWER = "0";
const char* DAY8_PART2_ANSWER = "0";
// Invalid array index, used in place of a forest-id
// to indicate something is not in any forest.
const size_t UNASSIGNED_FOREST = SIZE_MAX;

const static size_t TEST_JUNCTION_TARGET = 10;
const static size_t INPUT_JUNCTION_TARGET = 1000;

void day8(const char* filename)
{
    struct problem_inputs day8_lines = read_by_lines(filename);

    size_t target_junctions;
    if (strstr(filename, "test") != NULL) {
        target_junctions = TEST_JUNCTION_TARGET;
    } else {
        target_junctions = INPUT_JUNCTION_TARGET;
    }

    printf("Advent of Code, Day 08\n");
    printf("    ---------------------------------------------\n");
    printf("\t part 1: ");
    char* answer_part1 = day8_part1(day8_lines, target_junctions);

    printf("\t %s\n", answer_part1);

    printf("\t part 2: ");
    char* answer_part2 = day8_part2(day8_lines);

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


    if (answer_part1) { free(answer_part1); };
    if (answer_part2) { free(answer_part2); };
}

struct edge
{
    int64_t dist;
    size_t p1_pid;
    size_t p2_pid;
};

static int edge_compare(const void* p1, const void* p2)
{
    const struct edge* e1 = p1;
    const struct edge* e2 = p2;
    const int64_t left = e1->dist;
    const int64_t right = e2->dist;
    return ((left > right) - (left < right));
}

static void print_edge(struct edge e)
{
    printf("edge dist:%lld, pid1: %zu, pid2: %zu \t\t ",
           e.dist, e.p1_pid, e.p2_pid);
}

static int64_t calc_sqr_distance(struct point3 p1, struct point3 p2)
{
    int64_t dx = p1.x - p2.x;
    int64_t dy = p1.y - p2.y;
    int64_t dz = p1.z - p2.z;

    // squaring is a monotonic function for positive values, so n1 > n2 <=> n1^2 > n2^2
    // overhead of sqrt isn't a problem here, just don't want to be bother floating point values or an integer sqrt
    return (dx * dx) + (dy * dy) + (dz * dz);
}


// I think the process for connecting junctions is all set up properly. It is just spread across 2-3 manual connnects
// move into a look over the edge_arr from 0  until number of target junctions is reached (10 for test, 1000 for input)


static inline size_t min_size_t(const size_t a, const size_t b)
{
    return (a < b) ? a : b;
}

bool add_if_unique(struct size_vec* v, size_t d)
{
    for (size_t i = 0; i < v->len; i++) {
        if (v->arr[i] == d) {
            return false;
        }
    }
    push_size_vec(v, d);
    return true;
}

char* day8_part1(struct problem_inputs p_i, size_t target_junctions)
{
    println();
    printf("target_junctions: %zu\n", target_junctions);
    const size_t num_points = p_i.count;

    struct point3 points[num_points];
    size_t f_points[num_points]; // stores the forest that point is in
    for (size_t pid = 0; pid < num_points; pid++) {
        const struct point3 p_new = parse_3d_point_from_line(p_i.lines[pid]);
        points[pid] = p_new;
        f_points[pid] = pid; // each point starts in a singleton forest
    }
    const size_t num_edges = (num_points * (num_points - 1)) / 2;
    printf("num_edges: %zu, num_points: %zu\n", num_edges, num_points);

    printf("before building edge array\n");
    struct edge* edge_arr;
    edge_arr = malloc(num_edges * sizeof(struct edge));
    if (edge_arr == NULL) {
        printf("error malloc'ing edge_arr (size requested: %zu\n", num_edges * sizeof(struct edge));
    }
    // struct edge edge_arr[num_edges];
    size_t edge_idx = 0;
    printf("before building edge array 2\n");
    for (size_t p1 = 0; p1 < num_points; p1++) {
        for (size_t p2 = p1 + 1; p2 < num_points; p2++) {
            if (p1 == p2) {
                printf("ERROR: p1==p2 (%lld == %lld)  edge_count: %zu\n", p1, p2, edge_idx);
                exit(-1);
            }
            if (p1 > p2) {
                printf("ERROR: p1>p2 (%lld > %lld)  edge_count: %zu\n", p1, p2, edge_idx);
                exit(-1);
            }
            edge_arr[edge_idx].p1_pid = p1;
            edge_arr[edge_idx].p2_pid = p2;
            edge_arr[edge_idx].dist = calc_sqr_distance(points[p1], points[p2]);
            edge_idx++;
        }
    }
    printf("edge array build\n");
    // sort   struct edge dists[num_edges]; by edge.dist
    qsort(edge_arr, num_edges, sizeof(struct edge), edge_compare);
    printf("sort done\n");
    struct size_vec groups;
    init_size_vec(&groups);
    size_t j1_count = 0;

    for (size_t e_idx = 0; e_idx < num_edges; e_idx++) {
        struct edge current = edge_arr[e_idx];
        size_t g1, g2;
        g1 = f_points[current.p1_pid];
        g2 = f_points[current.p2_pid];
        // printf("\t edge[%zu] p1's group: %zu, p2's group: %zu\n", e_idx, g1, g2);
        if (g1 == g2) {
            // points are already connected
            continue;
        }

        size_t merge_to = min_size_t(g1, g2);
        f_points[current.p1_pid] = merge_to;
        f_points[current.p2_pid] = merge_to;
        add_if_unique(&groups, merge_to);
        j1_count++;

        if (j1_count >= target_junctions) {
            printf("junctions: %zu    e_idx= %zu\n", j1_count, e_idx);
            break;
        }
    }

    struct size_vec g_sizes;
    init_size_vec(&g_sizes);
    for (size_t i = 0; i < groups.len; i++) {
        size_t gid = groups.arr[i];
        size_t g_size = 0;
        for (size_t p = 0; p < num_points; p++) {
            if (f_points[p] == gid) {
                g_size++;
            }
        }
        // printf("group: %3zu, size: %zu\n", gid, g_size);
        if (g_size > 1) {
            push_size_vec(&g_sizes, g_size);
        }
    }

    printf("g_sizes: ");
    print_size_vec(g_sizes);
    println();
    printf("number of groups: %zu\n", g_sizes.len);
    qsort(g_sizes.arr, g_sizes.len, sizeof(size_t), size_t_compare_r);

    printf("g_sizes: ");
    print_size_vec(g_sizes);
    println();
    printf("number of groups: %zu\n", g_sizes.len);
    int64_t product = 1;
    for (size_t i = 0; i < 3; i++) {
        product = product * g_sizes.arr[i];
    }


    free(edge_arr);

    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, product);
    return answer;
}

char* day8_part2(struct problem_inputs p_i)
{
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}
