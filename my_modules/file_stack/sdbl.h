#ifndef FSTACK_H
#define FSTACK_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    size_t size;
    FILE *buf;
} stack_dbl;

void sdbl_init(stack_dbl *st, char * name);
void sdbl_destroy(stack_dbl *st);
bool sdbl_push(stack_dbl *st, double el);
double sdbl_pop(stack_dbl *st);
double sdbl_peek(stack_dbl *st);
bool sdbl_is_empty(stack_dbl *st);

#endif
