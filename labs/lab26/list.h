#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct listel listel;
struct listel {
    int val;
    int pn;
};

typedef struct {
    int pool_size;
    listel* buf;
    int barrier;
    int first;
    int size;
    int first_empty;
    int last_add;
} barrier_list;

bool list_init(barrier_list *l);
void list_destroy(barrier_list *l);
int list_get_size(barrier_list *l);

typedef struct {
    barrier_list *lst;
    int prev;
    int cur;
} list_iter;

list_iter list_iter_begin(barrier_list *l);
list_iter list_iter_end(barrier_list *l);
bool list_iter_equal(list_iter it1, list_iter it2);
void list_iter_move_next(list_iter *it);
void list_iter_move_back(list_iter *it);
int list_iter_get(list_iter *it);

void list_iter_set(list_iter *it, int val);
bool list_iter_insert_before(list_iter *it, int val);
void list_iter_remove(list_iter *it);

list_iter list_iter_find(barrier_list *l, int val);

#endif
