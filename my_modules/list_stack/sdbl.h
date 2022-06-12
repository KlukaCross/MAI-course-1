#ifndef SDBL_H
#define SDBL_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct stack_dbl_elem stack_dbl_elem;
struct stack_dbl_elem {
    double val;
    stack_dbl_elem *next;
};
typedef struct stack_dbl {
    stack_dbl_elem *top;
} stack_dbl;

void sdbl_init(stack_dbl *s);
void sdbl_destroy(stack_dbl *s);
bool sdbl_push(stack_dbl *s, double val);
double sdbl_pop(stack_dbl *s);
double sdbl_peek(stack_dbl *s);
bool sdbl_is_empty(stack_dbl *s);

#endif
