#ifndef MY_DYNAMIC_QUEUE_QDBL_H
#define MY_DYNAMIC_QUEUE_QDBL_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    size_t pool_size;
    size_t first;
    double *buf;
} queue_dbl;

void qdbl_init(queue_dbl *q);
void qdbl_destroy(queue_dbl *q);
bool qdbl_push(queue_dbl *q, double el);
double qdbl_pop(queue_dbl *q);
double qdbl_peek(queue_dbl *q);
bool qdbl_is_empty(queue_dbl *q);


#endif //MY_DYNAMIC_QUEUE_QDBL_H
