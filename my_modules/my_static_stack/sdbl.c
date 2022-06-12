
#include "sdbl.h"

void sdbl_init(stack_dbl *st) {
    st->size = 0;
}

void sdbl_destroy(stack_dbl *st) {
    st->size = 0;
}

bool sdbl_push(stack_dbl *st, double el) {
    if (st->size >= POOL_SIZE) {
        return false;
    }
    st->buf[st->size] = el;
    st->size++;
    return true;
}

double sdbl_pop(stack_dbl *st) {
   st->size--;
   return st->buf[st->size];
}

double sdbl_peek(stack_dbl *st) {
    return st->buf[st->size-1];
}

bool sdbl_is_empty(stack_dbl *st) {
    return st->size == 0;
}