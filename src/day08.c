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
const static size_t INPUT_JUNCTION_TARGET= 1000;

void day8(const char* filename) {
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
    char* answer_part1 = day8_part1(day8_lines,target_junctions);

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

struct edge{
    int64_t dist;
    size_t p1_pid;
    size_t p2_pid;
    size_t edge_id;
    size_t forest_id;
};

static int edge_compare(const void* p1, const void* p2)
{
    const struct edge* e1 = p1;
    const struct edge* e2 = p2;
    const int64_t left = e1->dist;
    const int64_t right = e2->dist;
    return ((left > right) - (left < right) );
}
static void print_edge(struct edge e)
{

    printf("edge id:%zu, dist:%lld, pid1: %zu, pid2: %zu \t\t ",
         e.edge_id,e.dist, e.p1_pid, e.p2_pid);
    if (e.forest_id == UNASSIGNED_FOREST) {
        printf(" not in forest");
    } else {
        printf("  in fid: %zu", e.forest_id);
    }
}

static int64_t calc_sqr_distance(struct point3 p1, struct point3 p2) {
    int64_t dx = p1.x - p2.x;
    int64_t dy = p1.y - p2.y;
    int64_t dz = p1.z - p2.z;

    // squaring is a monotonic function for positive values, so n1 > n2 <=> n1^2 > n2^2
    // overhead of sqrt isn't a problem here, just don't want to be bother floating point values or an integer sqrt
    return  (dx*dx) + (dy * dy) + (dz * dz);
}



// I think the process for connecting junctions is all set up properly. It is just spread across 2-3 manual connnects
// move into a look over the edge_arr from 0  until number of target junctions is reached (10 for test, 1000 for input)


char* day8_part1(struct problem_inputs p_i, size_t target_junctions) {
    println();
    printf("target_junctions: %zu\n", target_junctions);
    const size_t num_points = p_i.count;




    struct point3 points[num_points];
    size_t f_points[num_points]; // stores the forest that point is in
    for (size_t pid=0; pid < num_points; pid++) {
        const struct point3 p_new = parse_3d_point_from_line(p_i.lines[pid]);
        points[pid] = p_new;
        f_points[pid] = UNASSIGNED_FOREST;
    }




    const size_t num_edges= (num_points * (num_points-1)) / 2;
    printf("num_edges: %zu, num_points: %zu\n", num_edges, num_points);

    size_t edge_idx =0;
    struct edge edge_arr [num_edges];

    // represent all the forests, as an array of size_vec. Each size_vec has the edge_id of the edges in its
    // forest. This array is indexed by a forest_id, which is the edge_id of the first entry into a given forest.
    struct size_vec forests[num_edges];
    for (size_t i=0; i < num_edges; i++) {
        init_size_vec(&forests[i]);
    }

    for (size_t p1=0; p1 < num_points; p1++) {
        for (size_t p2=p1 + 1; p2 < num_points; p2++ ) {
            if (p1 == p2) {
                printf("ERROR: p1==p2 (%lld == %lld)  edge_count: %zu\n", p1,p2, edge_idx );
                exit(-1);
            }
            if (p1 > p2) {
                printf("ERROR: p1>p2 (%lld > %lld)  edge_count: %zu\n", p1,p2, edge_idx );
                exit(-1);
            }

            edge_arr [edge_idx].p1_pid = p1;
            edge_arr [edge_idx].p2_pid = p2;
            edge_arr [edge_idx].dist = calc_sqr_distance(points[p1], points[p2]);
            edge_arr [edge_idx].edge_id = edge_idx;
            edge_arr [edge_idx].forest_id = UNASSIGNED_FOREST;
            edge_idx++;
        }
    }
    if (edge_idx != num_edges) {
        printf("ERROR: made edge_idx: %zu pairs, when there should be %zu\n", edge_idx, num_edges);
        exit(-1);
    }

    println();

    // sort   struct edge dists[num_edges]; by edge.dist

    qsort(edge_arr, num_edges, sizeof(struct edge), edge_compare);




    size_t junction_count =0; // increment assign a forest_id to a point that didn't have one (via f_points)
    printf( "junctions: %zu, left %zu\n", junction_count, num_points - junction_count );




    /*-----------------------------------------------------------------------------------*/
    // connecting initial edge to forest
    size_t e_idx =0;  // index into edge_arr, of the first edge that hasn't been processed.
    struct edge next = edge_arr[e_idx];
    e_idx++;

    if (next.forest_id != UNASSIGNED_FOREST) {
        printf("initial closed edge is already in forest: %zu\n ", next.forest_id);
        exit(-1);
    }

    next.forest_id = next.edge_id;   // forest array is indexed by the first edge in a given forest
    push_size_vec(&forests[next.forest_id], next.edge_id);





    printf("closest edge inserted into forest_id: %zu,  forest size: %zu, new e_idx: %zu\n\t",
        next.forest_id,  forests[next.forest_id].len, e_idx);
    if (f_points[next.p1_pid] != UNASSIGNED_FOREST) {
        printf("\npoint id: %zu, ",next.p1_pid);
        print_point3(points[next.p1_pid]);
        printf(" is already in forest: %zu\n", f_points[next.p1_pid]);
        exit(-1);
    }
    if (f_points[next.p2_pid] != UNASSIGNED_FOREST) {
        printf("\npoint id: %zu, ",next.p2_pid );
        print_point3(points[next.p2_pid]);
        printf(" is already in forest: %zu\n", f_points[next.p2_pid]);
        exit(-1);
    }
    // mark points as being in forest
    if (f_points[next.p1_pid] == UNASSIGNED_FOREST) {
        junction_count++;
        f_points[next.p1_pid] = next.forest_id;
    } else {
        if (f_points[next.p1_pid] != next.forest_id) {
            printf("\np1 (%zu) is connected to forest %zu, when trying to connect to forest: %zu\n", next.p1_pid, f_points[next.p1_pid], next.forest_id );
            exit(-1);
        }
    }
    if (f_points[next.p2_pid] == UNASSIGNED_FOREST) {
        junction_count++;
        f_points[next.p2_pid] = next.forest_id;
    } else {
        if (f_points[next.p2_pid] != next.forest_id) {
            printf("\np2 (%zu) is connected to forest %zu, when trying to connect to forest: %zu\n", next.p2_pid, f_points[next.p2_pid], next.forest_id );
            exit(-1);
        }
    }

    print_edge(next);
    println();
    printf("\tpid1: %zu -> ", next.p1_pid);
    print_point3(points[next.p1_pid]);
    printf("\tpid2: %zu -> ", next.p2_pid);
    print_point3(points[next.p2_pid]);
    println();

    // end assignment.



    next = edge_arr[e_idx];
    e_idx++;


    printf("\nnext: \n\t"); print_edge(next); println();
    printf("\tpid1: %zu -> ", next.p1_pid);
    print_point3(points[next.p1_pid]);
    printf("\tpid2: %zu -> ", next.p2_pid);
    print_point3(points[next.p2_pid]);
    println();

    if (next.forest_id == UNASSIGNED_FOREST) {
        printf("\tnext is not assigned to forest\n");
    } else {
        printf("\tnext is already assigned to forest %zu\n", next.forest_id);
    }

    if ((f_points[next.p1_pid] == UNASSIGNED_FOREST) && (f_points[next.p2_pid]== UNASSIGNED_FOREST)) {
        printf("next both points (%zu,%zu) are not in a forest\n",next.p1_pid, next.p2_pid );
    } else {
        if (f_points[next.p1_pid] != UNASSIGNED_FOREST) {
            printf("\t\tpoint (%zu) is in forest %zu\n", next.p1_pid, f_points[next.p1_pid]);
        }
        if (f_points[next.p2_pid] != UNASSIGNED_FOREST) {
            printf("\t\tpoint (%zu) is in forest %zu\n", next.p2_pid, f_points[next.p2_pid]);\
        }
    }


    //connect next to forest
    if (next.forest_id != UNASSIGNED_FOREST) {
        printf("next (eid: %zu) is already in forest %zu\n", next.edge_id, next.forest_id);
        exit(-1);
    }

    if (f_points[next.p1_pid] != UNASSIGNED_FOREST) {
        next.forest_id = f_points[next.p1_pid];
        junction_count++;
    } else if (f_points[next.p2_pid] != UNASSIGNED_FOREST) {
        next.forest_id = f_points[next.p2_pid];
        junction_count++;
    } else {
        // if neither point links the edge to a forest, we connect to a new forest based on edge_id
        next.forest_id = next.edge_id;
    }
    printf("2connecting edge: %zu to forest: %zu\n", next.edge_id, next.forest_id);
    if (f_points[next.p1_pid] == UNASSIGNED_FOREST) {

        f_points[next.p1_pid] = next.forest_id;
    } else {
        if (f_points[next.p1_pid] != next.forest_id) {
            printf("\np1 (%zu) is connected to forest %zu, when trying to connect to forest: %zu\n", next.p1_pid, f_points[next.p1_pid], next.forest_id );
            exit(-1);
        }
    }
    if (f_points[next.p2_pid] == UNASSIGNED_FOREST) {

        f_points[next.p2_pid] = next.forest_id;
    } else {
        if (f_points[next.p2_pid] != next.forest_id) {
            printf("\np2 (%zu) is connected to forest %zu, when trying to connect to forest: %zu\n", next.p2_pid, f_points[next.p2_pid], next.forest_id );
            exit(-1);
        }
    }


    f_points[next.p2_pid] = next.forest_id;
    size_t r = push_size_vec(&forests[next.forest_id], next.edge_id);

    printf("edge %zu assigned to forest %zu, forest size now: %zu. \t  junctions: %zu, left %zu\n", next.edge_id, next.forest_id,r+1,
         junction_count, num_points - junction_count);





    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}

char* day8_part2(struct problem_inputs p_i) {
    char* answer = malloc(ANSWER_BUFFER_SIZE);
    sprintf(answer, "%"PRId64, p_i.count);
    return answer;
}