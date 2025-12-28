// ReSharper disable CppDFAMemoryLeak
#include "ds.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//---------------- int64_vec functions start------------------
void push_int64_vec(struct int64_vec* v, const int64_t d){
    if (v->arr == NULL) {
        v->arr = malloc(2 * sizeof(int64_t));
        v->len = 1;
        v->cap = 2;
        v->arr[0] = d;
        return;
    }

    if (v->len < v->cap) {
        v->arr[v->len] = d;
        v->len++;
        return;
    }

    if (v->len == v->cap) {
        const size_t old_cap = v->cap;
        const size_t new_cap = old_cap * 2;
        void* tmp = realloc(v->arr, new_cap * sizeof(int64_t));
        if (tmp == NULL) {
            printf("error, %s:%d:realloc failed (old %zu -> new %zu\n", __func__, __LINE__, old_cap, new_cap);
            free(tmp);
            v->arr = NULL;
            exit(-1);
        } else {
            v->arr = tmp;
        }
        v->cap = new_cap;
        v->arr[v->len] = d;
        v->len++;
    }
}

void free_int64_vec(struct int64_vec* v){
    free(v->arr);
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
}

void print_int64_vec(const struct int64_vec v){
    if (v.arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v.len; i++) {
        printf("%"PRId64, v.arr[i]);
        if (i + 1 < v.len) {
            printf(", ");
        }
    }
    printf("]");
}


void print_int64_vec_rev(const struct int64_vec v){
    if (v.arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = v.len - 1; i > 0; i--) {
        printf("%"PRId64, v.arr[i]);

        printf(", ");
    }
    printf("%"PRId64, v.arr[0]);
    printf("]");
}


void init_int64_vec(struct int64_vec* v){
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
}

//---------------- int64_vec functions end------------------


//---------------- size_vec functions start------------------
size_t push_size_vec(struct size_vec* v, const size_t d){
    if (v->arr == NULL) {
        v->arr = malloc(2 * sizeof(size_t));
        v->len = 1;
        v->cap = 2;
        v->arr[0] = d;
        return 0;
    }

    if (v->len < v->cap) {
        v->arr[v->len] = d;
        v->len++;
        return (v->len - 1);
    }

    if (v->len == v->cap) {
        const size_t old_cap = v->cap;
        const size_t new_cap = old_cap * 2;
        void* tmp = realloc(v->arr, new_cap * sizeof(size_t));
        if (tmp == NULL) {
            printf("error, %s:%d:realloc failed (old %zu -> new %zu\n", __func__, __LINE__, old_cap, new_cap);
            free(tmp);
            v->arr = NULL;
            exit(-1);
        } else {
            v->arr = tmp;
        }
        v->cap = new_cap;
        v->arr[v->len] = d;
        v->len++;
    }
    return SIZE_MAX;
}


void free_size_vec(struct size_vec* v){
    free(v->arr);
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
}

void print_size_vec(const struct size_vec v){
    if (v.arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v.len; i++) {
        printf("%zu", v.arr[i]);
        if (i + 1 < v.len) {
            printf(", ");
        }
    }
    printf("]");
}


void print_size_vec_rev(const struct size_vec v){
    if (v.arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = v.len - 1; i > 0; i--) {
        printf("%zu", v.arr[i]);

        printf(", ");
    }
    printf("%zu", v.arr[0]);
    printf("]");
}


void init_size_vec(struct size_vec* v){
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
}

void init_size_vec_with_size(struct size_vec* v, const size_t init_size){
    v->arr = malloc(sizeof(size_t) * init_size);
    v->len = 0;
    v->cap = init_size;
}

//newly allocated array is return
size_t* size_vec_to_array(const struct size_vec* v){
    size_t* r = malloc(sizeof(size_t) * v->len);
    for (size_t i=0; i < v->len; i++) {
        r[i] = v->arr[i];
    }
    return r;
}


//---------------- size_vec functions end------------------

//----------------  f_string and queue_fs ops -----------------


// allocated returned and returned->str
struct fstring* new_fstring(const char* s){
    struct fstring* fs = malloc(sizeof(struct fstring));
    fs->len = strlen(s);
    fs->str = strdup(s);
    return fs;
}

// allocated returned and returned->str
struct fstring* new_fstringn(const char* s, const size_t n){
    struct fstring* fs = malloc(sizeof(struct fstring));
    fs->len = n;
    fs->str = malloc(sizeof(char) * (n + 1));
    for (size_t i = 0; i < n; i++) {
        fs->str[i] = s[i];
    }
    fs->str[n] = '\0';
    return fs;
}
void free_fstring(struct fstring* s){
    if (s->len != 0) {
        free(s->str);
        s->str = 0;
    }
}
struct fstring* fstr_dup(const fstring* s){
    struct fstring* f = malloc(sizeof(fstring));
    if (f==NULL) {
        printf("error, %s:%d:malloc failed for fsrting: %s (%zu)\n", __func__, __LINE__, s->str, s->len);
        exit(-1);
    }
    f->str = strdup(s->str);
    f->len = s->len;
    return f;
}
int fstrcmp(const fstring* s1, const fstring* s2){
    const size_t left = s1->len;
    const size_t right = s2->len;
    if (left != right) {
        return ((left > right) - (left < right));
    }
    return strncmp(s1->str,s2->str, left);
}



struct queue_fs* create_queue_fs(){
    struct queue_fs* new_q = malloc(sizeof(struct queue_fs));
    new_q->head = NULL;
    new_q->tail = NULL;
    new_q->len = 0;
    return new_q;
}

void free_queue_fs(struct queue_fs* q){
    while (q->len > 0) {
        struct node_fs* n = pop_front_queue_fs(q);
        free(n);
    }
}

// fill allocate struct node_fs on heap
void front_push_queue_fs(struct queue_fs* q, struct fstring* s){
    struct node_fs* node = malloc(sizeof(struct node_fs));
    node->data = s;
    node->next = q->head;
    if (q->len == 0) {
        q->head = node;
        q->tail = node;
        q->len = 1;
    } else {
        q->len++;
        q->head = node;
    }
}

// fill allocate struct node_fs on heap
void front_back_queue_fs(struct queue_fs* q, struct fstring* s){
    struct node_fs* node = malloc(sizeof(struct node_fs));
    node->data = s;
    node->next = NULL;
    if (q->len == 0) {
        q->head = node;
        q->tail = node;
        q->len = 1;
    } else {
        q->tail->next = node;
        q->tail = node;
        q->len++;
    }
}

// no deallocation done
struct node_fs* pop_front_queue_fs(struct queue_fs* q){
    if (q->len == 0) {
        printf("pop_from_queue_fs on empty queue\n");
        exit(-1);
    }

    struct node_fs* node = q->head;
    if (q->len == 1) {
        q->head = NULL;
        q->tail = NULL;
        q->len = 0;
        return node;
    }

    q->head = node->next;
    q->len--;
    if (q->len == 1) {
        q->tail = node;
    }
    return node;
}

void print_queue_fs(const struct queue_fs* q){
    if (q->len == 0) {
        printf("[]");
        return;
    }
    if (q->len == 1) {
        printf("[\"%s\"]", q->head->data->str);
        return;
    }
    printf("[");
    const struct node_fs* current = q->head;
    while (current != q->tail) {
        printf("\"%s\", ", current->data->str);
        current = q->head->next;
    }
    printf("\"%s\"", current->data->str);
    printf("]");
}
//----------------  fstr_vec -----------------

void init_fstr_vec(struct fstr_vec* v){
    v->arr=NULL;
    v->len=0;
    v->cap=0;
}

void init_fstr_vec_n(struct fstr_vec* v, size_t n){
    if (n ==0) {
        v->arr = NULL;
    } else {
        v->arr = malloc(n * sizeof(fstring*));
    }
    v->len=0;
    v->cap=n;
}

// takes ownership of the allocated fstring. This is mainly to support push_fstr_vec_cn
static void push_fstr_vec_raw(struct fstr_vec* v,  fstring* s){
    if (v->arr == NULL) {
        v->arr = malloc(2 * sizeof(fstring*));
        v->len = 1;
        v->cap = 2;
        v->arr[0] = s;
        return;
    }

    if (v->len < v->cap) {
        v->arr[v->len] = s;
        v->len++;
        return;
    }

    if (v->len == v->cap) {
        const size_t old_cap = v->cap;
        const size_t new_cap = old_cap * 2;
        void* tmp = realloc(v->arr, new_cap * sizeof(fstring*));
        if (tmp == NULL) {
            printf("error, %s:%d:realloc failed (old %zu -> new %zu\n", __func__, __LINE__, old_cap, new_cap);
            free(tmp);
            v->arr = NULL;
            exit(-1);
        } else {
            v->arr = tmp;
        }
        v->cap = new_cap;
        v->arr[v->len] = s;
        v->len++;
    }
}






void push_fstr_vec(struct fstr_vec* v, const fstring* s){
    fstring* new_f = fstr_dup(s);
    push_fstr_vec_raw(v, new_f);
}

// inserts newly allocated fstring for the provided cstr
void push_fstr_vec_c(struct fstr_vec* v, const char* cstr){
    const size_t len = strlen(cstr);
    fstring* new_f = malloc(sizeof(fstring));
    new_f->str = malloc((len+1) * sizeof(char));
    new_f->len = len;
    memcpy(new_f->str, cstr, len);
    new_f->str[len] = '\0';
    push_fstr_vec_raw(v, new_f);
}
/** inserts newly allocated fstring, a new cstr is allocated with length len (owned by the new fstring)
*   this is for when you know the length of the string, and are inserting from a buffer that might not be
*   null-terminated
 */
void push_fstr_vec_cn(struct fstr_vec* v, const char* cstr, size_t len){
    fstring* new_f = malloc(sizeof(fstring));
    new_f->str = malloc((len+1) * sizeof(char));
    new_f->len = len;
    memcpy(new_f->str, cstr, len);
    new_f->str[len] = '\0';
    push_fstr_vec_raw(v, new_f);
}


void free_fstr_vec(struct fstr_vec* v){
    for (size_t i=0; i< v->len; i++) {
        free_fstring(v->arr[i]);
    }
    if (v->cap != 0) {
        free(v->arr);
        v->cap =0;
        v->len =0;
    }
}
void print_fstr_vec(const struct fstr_vec* v){
    if (v->arr == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v->len; i++) {
        printf("\"%s\"", v->arr[i]->str);
        if (i + 1 < v->len) {
            printf(", ");
        }
    }
    printf("]");
}


bool contains_fstr_vec(const struct fstr_vec* v, const fstring* s){
    for (size_t i=0; i < v->len; i++) {
        if (fstrcmp(v->arr[i], s) == 0) {
            return true;
        }
    }
    return false;
}








//----------------  str_vec -----------------
void init_str_vec(struct str_vec* v){
    v->len = 0;
    v->cap = 0;
    v->arr = NULL;
}

void push_str_vec(struct str_vec* v, const char* s){
    if (v->arr == NULL) {
        v->arr = malloc(2 * sizeof(char*));
        v->len = 1;
        v->cap = 2;
        v->arr[0] = strdup(s);
        return;
    }

    if (v->len < v->cap) {
        v->arr[v->len] = strdup(s);
        v->len++;
        return;
    }

    if (v->len == v->cap) {
        const size_t old_cap = v->cap;
        const size_t new_cap = old_cap * 2;
        void* tmp = realloc(v->arr, new_cap * sizeof(char*));
        if (tmp == NULL) {
            printf("error, %s:%d:realloc failed (old %zu -> new %zu\n", __func__, __LINE__, old_cap, new_cap);
            free(tmp);
            v->arr = NULL;
            exit(-1);
        } else {
            v->arr = tmp;
        }
        v->cap = new_cap;
        v->arr[v->len] = strdup(s);
        v->len++;
    }
}

void free_str_vec(struct str_vec* v){
    for (size_t i = 0; i < v->len; i++) {
        free(v->arr[i]);
    }
    if (v->cap !=0) {
        free(v->arr);
        v->cap =0;
    }
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
}

void print_str_vec(const struct str_vec* v){
    if (v->arr == NULL) {
        printf("Array is NULL\n");
        return;
    }
    printf("[");
    for (size_t i = 0; i < v->len; i++) {
        printf("\"%s\"", v->arr[i]);
        if (i + 1 < v->len) {
            printf(", ");
        }
    }
    printf("]");
}
bool contains_str_vec(const struct str_vec* v, const char* s){
    for (size_t i=0; i < v->len; i++) {
        if (strcmp(v->arr[i], s) == 0) {
            return true;
        }
    }
    return false;
}


void push_void_vec(struct void_vec* v, void* d){
    if (v->arr == NULL) {
        v->arr = malloc(2 * sizeof(void*));
        v->len = 1;
        v->cap = 2;
        v->arr[0] = d;
        return;
    }

    if (v->len < v->cap) {
        v->arr[v->len] = d;
        v->len++;
        return;
    }

    if (v->len == v->cap) {
        const size_t old_cap = v->cap;
        const size_t new_cap = old_cap * 2;
        void* tmp = realloc(v->arr, new_cap * sizeof(void*));
        if (tmp == NULL) {
            printf("error, %s:%d:realloc failed (old %zu -> new %zu\n", __func__, __LINE__, old_cap, new_cap);
            free(tmp);
            v->arr = NULL;
            exit(-1);
        } else {
            v->arr = tmp;
        }
        v->cap = new_cap;
        v->arr[v->len] = d;
        v->len++;
    }

}
void init_void_vec(struct void_vec* v){
    v->arr = NULL;
    v->len=0;
    v->cap=0;
}
void init_void_vec_with_size(struct void_vec* v, size_t init_size){
    v->arr = malloc(sizeof(void*) * init_size);
    v->len=0;
    v->cap = init_size;
}
void free_void_vec(struct void_vec* v ){
    free(v->arr);
    v->len =0;
    v->cap =0;
}

//----------------------------------------------------------------------------


void push_stst_vec(struct stst_vec* v, const struct size_vec* d){
    if (v->arr == NULL) {
        v->arr = malloc(2 * sizeof(struct size_vec));
        v->len = 1;
        v->cap = 2;
        init_size_vec_with_size(&v->arr[0], d->len);
        memcpy(v->arr[0].arr, d->arr, sizeof(struct size_vec) * d->len);
        v->arr[0].len = d->len;
        return;
    }

    if (v->len < v->cap) {
        init_size_vec_with_size(&v->arr[v->len ], d->len);
        memcpy(v->arr[v->len ].arr, d->arr, sizeof(struct size_vec) * d->len);
        v->arr[v->len ].len = d->len;
        v->len++;
        return;
    }

    if (v->len == v->cap) {
        const size_t old_cap = v->cap;
        const size_t new_cap = old_cap * 2;
        void* tmp = realloc(v->arr, new_cap * sizeof(struct size_vec));
        if (tmp == NULL) {
            printf("error, %s:%d:realloc failed (old %zu -> new %zu\n", __func__, __LINE__, old_cap, new_cap);
            free(tmp);
            v->arr = NULL;
            exit(-1);
        } else {
            v->arr = tmp;
        }
        v->cap = new_cap;
        init_size_vec_with_size(&v->arr[v->len ], d->len);
        memcpy(v->arr[v->len ].arr, d->arr, sizeof(struct size_vec) * d->len);
        v->arr[v->len ].len = d->len;
        v->len++;
    }
}





void init_stst_vec(struct stst_vec* v){
    v->arr = NULL;
    v->len=0;
    v->cap=0;
}
void init_stst_vec_with_size(struct stst_vec* v, size_t init_size){
    v->arr = malloc(init_size * sizeof(struct size_vec));
    v->len =0;
    v->cap = init_size;
}

void free_stst_vec(struct stst_vec* v){
    for (size_t i=0; i < v->len; i++) {
        free_size_vec(&v->arr[i]);
    }
    free(v->arr);
    v->arr = NULL;
    v->len =0;
    v->cap =0;
}

// return index if found, SIZE_MAX if not found
size_t find_stst_vec(const struct stst_vec* v, const struct size_vec *d){
    for (size_t i=0; i < v->len;i++) {
        if (v->arr[i].len != d->len) {
            continue;
        }
        for (size_t j=0; j < d->len; j++) {
            if (v->arr[i].arr[j] != d->arr[j]) {
                break;
            }
        }
        return i;
    }
    return SIZE_MAX;
}