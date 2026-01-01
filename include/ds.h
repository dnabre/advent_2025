#ifndef ADVENT_2025_DS_H
#define ADVENT_2025_DS_H
#include "c17_strict.h"
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
struct size_vec* size_vec_dup(const struct size_vec*);
struct size_vec* size_vec_dup_n(const struct size_vec* v, size_t n);


/* fixed length string. null-terminated,
 * len doesn't include null character, str is heap allocated.
 * intention is for these to be editable
*/
typedef struct fstring {
    char* str;
    size_t len;
} fstring;

struct node_sv {
    struct size_vec* data;
    struct node_sv* next;
};

struct queue_sv {
    struct node_sv* head;
    struct node_sv* tail;
    size_t len;
};


/* -------------------------------  fstring stuff --------------------------------  */
// unless stated, no fstring objects are allocated. that's left to user to keep track of.


/* returns newly allocated fstring of the given null-terminted string.
 * new fstring will contain a newly allocated duplicate of provided string
 */
fstring* new_fstring(const char*);

/* same as new_fstring, but the provided string is not assumed to be null-terminated, and only the first
 * `n` characters are used
 */
fstring* new_fstringn(const char*, size_t n);

// fstring struct always owns its memory.
void free_fstring(fstring* s);

fstring* fstr_dup(const fstring* s);


struct fstr_vec {
    fstring** arr;
    size_t len;
    size_t cap;
};

void init_fstr_vec(struct fstr_vec*);
void init_fstr_vec_n(struct fstr_vec*, size_t);

// copies string being inserted
void push_fstr_vec(struct fstr_vec* v, const fstring* s);
void push_fstr_vec_c(struct fstr_vec* v, const char* cstr);
void push_fstr_vec_cn(struct fstr_vec* v, const char* cstr, size_t len);
void free_fstr_vec(struct fstr_vec*);
void print_fstr_vec(const struct fstr_vec*);
bool contains_fstr_vec(const struct fstr_vec*, const fstring*);

//----------------------
// gives clean, newly heap allocated
struct queue_sv* create_queue_sv(void);

// frees the struct queue_fs and any struct node_fs  that in the queue
void free_queue_sv(struct queue_sv*);


// will allocate struct node_fs on heap
void push_front_queue_sv(struct queue_sv*, struct size_vec*);
// will allocate struct node_fs on heap
void push_back_queue_sv(struct queue_sv*, struct size_vec*);

// no deallocation done
struct node_sv* pop_front_queue_sv(struct queue_sv*);

void print_queue_sv(const struct queue_sv*);


struct str_vec {
    char** arr;
    size_t len;
    size_t cap;
};

void init_str_vec(struct str_vec*);

// copies string being inserted
void push_str_vec(struct str_vec* v, const char* s);
void free_str_vec(struct str_vec*);
void print_str_vec(const struct str_vec*);
bool contains_str_vec(const struct str_vec*, const char*);


// static bool grow_size_vec(struct size_vec* v, const size_t ptrsize, size_t* curcount);


//-------------------------


struct void_vec {
    void** arr;

    size_t len;
    size_t cap;
};

void push_void_vec(struct void_vec* v, void* d);
void init_void_vec(struct void_vec*);
void init_void_vec_with_size(struct void_vec*, size_t init_size);
void free_void_vec(struct void_vec*);


// dynamic array of struct size_vec. size_vec structs are copy'd into the stst_vec
struct stst_vec {
    struct size_vec* arr;
    size_t len;
    size_t cap;
};

void push_stst_vec(struct stst_vec* v, const struct size_vec* d);
void init_stst_vec(struct stst_vec*);
void init_stst_vec_with_size(struct stst_vec*, size_t init_size);
// return index if found, SIZE_MAX if not found
size_t find_stst_vec(const struct stst_vec* v, const struct size_vec* d);
void free_stst_vec(struct stst_vec*);


#endif //ADVENT_2025_DS_H
