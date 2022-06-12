#ifndef SDBL_H
#define SDBL_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    size_t pool_size;
    double *buf;
} stack_dbl;

void sdbl_init(stack_dbl *st);
void sdbl_destroy(stack_dbl *st);
bool sdbl_push(stack_dbl *st, double el);
double sdbl_pop(stack_dbl *st);
double sdbl_peek(stack_dbl *st);
bool sdbl_is_empty(stack_dbl *st);

#endif
