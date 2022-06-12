#include "sdbl.h"

void sdbl_init(stack_dbl *s) {
    s->top = NULL;
}

bool sdbl_is_empty(stack_dbl *s) {
    return s->top == NULL;
}

double sdbl_peek(stack_dbl *s) {
    return s->top->val;
}

bool sdbl_push(stack_dbl *s, double val) {
    stack_dbl_elem *new_el = malloc(sizeof(stack_dbl_elem));
    if (new_el == NULL) return false;
    new_el->val = val;
    new_el->next = s->top;
    s->top = new_el;
    return true;
}

double sdbl_pop(stack_dbl *s) {
    stack_dbl_elem *tmp = s->top;
    s->top = s->top->next;
    double res = tmp->val;
    free(tmp);
    return res;
}

void sdbl_destroy(stack_dbl *s) {
    while (!sdbl_is_empty(s)) {
        sdbl_pop(s);
    }
}