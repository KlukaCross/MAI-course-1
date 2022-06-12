#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct listel listel;
struct listel {
    double val;
    listel *pn;
};

typedef struct {
    listel barrier;
    listel* first;
    int size;
} barrier_list;

void list_init(barrier_list *l);
void list_destroy(barrier_list *l);
int get_size(barrier_list *l);

typedef struct {
    barrier_list *lst;
    listel *prev;
    listel *cur;
} list_iter;

list_iter list_iter_begin(barrier_list *l);
list_iter list_iter_end(barrier_list *l);
bool list_iter_equal(list_iter it1, list_iter it2);
void list_iter_move_next(list_iter *it);
double list_iter_get(list_iter *it);

void list_iter_set(list_iter *it, double val);
void list_iter_insert_before(list_iter *it, double val);
void list_iter_remove(list_iter *it);

#endif
