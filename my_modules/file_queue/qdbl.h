#ifndef QDBL_H
#define QDBL_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    size_t size;
    size_t first;
    FILE *buf;
} queue_dbl;

void qdbl_init(queue_dbl *q, char * name);
void qdbl_destroy(queue_dbl *q);
bool qdbl_push(queue_dbl *q, double el);
double qdbl_pop(queue_dbl *q);
double qdbl_peek(queue_dbl *q);
bool qdbl_is_empty(queue_dbl *q);

#endif
