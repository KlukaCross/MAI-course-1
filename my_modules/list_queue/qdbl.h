#ifndef QDBL_H
#define QDBL_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue_dbl_elem queue_dbl_elem;
struct queue_dbl_elem {
    double val;
    queue_dbl_elem *next;
};

typedef struct queue_dbl {
    queue_dbl_elem *first;
    queue_dbl_elem *last;
} queue_dbl;

void qdbl_init(queue_dbl *q);
void qdbl_destroy(queue_dbl *q);
bool qdbl_push(queue_dbl *q, double val);
double qdbl_pop(queue_dbl *q);
double qdbl_peek(queue_dbl *q);
bool qdbl_is_empty(queue_dbl *q);

#endif
