#ifndef DDBL_H
#define DDBL_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct deque_dbl_elem deque_dbl_elem;
struct deque_dbl_elem {
    double val;
    deque_dbl_elem *next;
    deque_dbl_elem *prev;
};

typedef struct deque_dbl {
    deque_dbl_elem *first;
    deque_dbl_elem *last;
} deque_dbl;

void ddbl_init(deque_dbl *d);
void ddbl_destroy(deque_dbl *d);
bool ddbl_push_front(deque_dbl *d, double val);
bool ddbl_push_back(deque_dbl *d, double val);
double ddbl_pop_front(deque_dbl *d);
double ddbl_pop_back(deque_dbl *d);
double ddbl_peek_front(deque_dbl *d);
double ddbl_peek_back(deque_dbl *d);
bool ddbl_is_empty(deque_dbl *d);



#endif
