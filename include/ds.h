#ifndef ADVENT_2025_DS_H
#define ADVENT_2025_DS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct int64_vec {
    int64_t* arr;
    size_t len;
    size_t cap;
};

void push_int64_vec(struct int64_vec* v, int64_t d);
void free_int64_vec(struct int64_vec*);
void print_int64_vec(struct int64_vec);
void print_int64_vec_rev(struct int64_vec);
void init_int64_vec(struct int64_vec*);


struct size_vec {
    size_t* arr;
    size_t len;
    size_t cap;
};

size_t push_size_vec(struct size_vec* v, size_t d);
void free_size_vec(struct size_vec*);
void print_size_vec(struct size_vec);
void print_size_vec_rev(struct size_vec);
void init_size_vec(struct size_vec*);
void init_size_vec_with_size(struct size_vec*, size_t init_size);


/* fixed length string. null-terminated,
 * len doesn't include null character, str is heap allocated.
 * intention is for these to be editable
*/
struct f_string {
    char* str;
    size_t len;
};

struct node_fs {
    struct f_string* data;
    struct node_fs* next;
};

struct queue_fs {
    struct node_fs* head;
    struct node_fs* tail;
    size_t len;
};


/* -------------------------------  struct f_string stuff --------------------------------  */
// unless stated, no struct f_string objects are allocated. that's left to user to keep track of.


/* returns newly allocated f_string of the given null-terminted string.
 * new f_string will contain a newly allocated duplicate of provided string
 */
struct f_string* new_fstring(const char*);

/* same as new_fstring, but the provided string is not assumed to be null-terminated, and only the first
 * `n` characters are used
 */
struct f_string* new_fstringn(const char*,size_t n);



// gives clean, newly heap allocated
struct queue_fs* create_queue_fs();

// frees the struct queue_fs and any struct node_fs  that in the queue
void free_queue_fs(struct queue_fs*);


// fill allocate struct node_fs on heap
void front_push_queue_fs(struct queue_fs*, struct f_string*);
// fill allocate struct node_fs on heap
void front_back_queue_fs(struct queue_fs*, struct f_string*);

// no deallocation done
struct node_fs*  pop_front_queue_fs(struct queue_fs *);

void print_queue_fs(const struct queue_fs*);


struct str_vec {
    char** arr;
    size_t len;
    size_t cap;
};

void init_str_vec(struct str_vec*);

// copies string being inserted
void push_str_vec(struct str_vec* v, const char* s);
void free_str_vec(struct str_vec*);
void print_str_vec(struct str_vec);
bool contains_str_vec(const struct str_vec*, const char*);



// static bool grow_size_vec(struct size_vec* v, const size_t ptrsize, size_t* curcount);


#endif //ADVENT_2025_DS_H
