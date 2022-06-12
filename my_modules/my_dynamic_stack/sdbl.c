#include <stdio.h>
#include "sdbl.h"

static bool grow_buffer(stack_dbl *st) {
    size_t new_size = st->pool_size * 2;
    if (st->pool_size == 0) new_size = 4;
    double *new_buf = realloc(st->buf, new_size * sizeof(double));
    if (new_buf == NULL) return false;
    st->buf = new_buf;
    st->pool_size = new_size;
    return true;
}

void sdbl_init(stack_dbl *st) {
    st->size = 0;
    st->buf = NULL;
    st->pool_size = 0;
}

void sdbl_destroy(stack_dbl *st) {
    st->size = 0;
    st->pool_size = 0;
    free(st->buf);
    st->buf = NULL;
}

bool sdbl_push(stack_dbl *st, double el) {
    if (st->size >= st->pool_size) {
        if (!grow_buffer(st)) return false;
    }
    st->buf[st->size] = el;
    st->size++;
    return true;
}

double sdbl_pop(stack_dbl *st) {
    double res = st->buf[st->size-1];
    st->size--;
    if (st->size * 4 == st->pool_size) {
        st->pool_size = st->pool_size / 2;
        st->buf = realloc(st->buf, st->pool_size * sizeof(double));
    }
    return res;
}

double sdbl_peek(stack_dbl *st) {
    return st->buf[st->size-1];
}

bool sdbl_is_empty(stack_dbl *st) {
    return st->size == 0;
}
