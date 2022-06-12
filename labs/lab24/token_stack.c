#include "token_stack.h"

static bool grow_buffer(stack_token *st) {
    size_t new_size = st->pool_size * 2;
    if (st->pool_size == 0) new_size = 4;
    token *new_buf = realloc(st->buf, new_size * sizeof(token));
    if (new_buf == NULL) return false;
    st->buf = new_buf;
    st->pool_size = new_size;
    return true;
}

void stok_init(stack_token *st) {
    st->size = 0;
    st->buf = NULL;
    st->pool_size = 0;
}

void stok_destroy(stack_token *st) {
    st->size = 0;
    st->pool_size = 0;
    free(st->buf);
    st->buf = NULL;
}

bool stok_push(stack_token *st, token el) {
    if (st->size >= st->pool_size) {
        if (!grow_buffer(st)) return false;
    }
    st->buf[st->size] = el;
    st->size++;
    return true;
}

token stok_pop(stack_token *st) {
    token res = st->buf[st->size-1];
    st->size--;
    if (st->size * 4 == st->pool_size) {
        st->pool_size = st->pool_size / 2;
        st->buf = realloc(st->buf, st->pool_size * sizeof(token));
    }
    return res;
}

token stok_peek(stack_token *st) {
    return st->buf[st->size-1];
}

bool stok_is_empty(stack_token *st) {
    return st->size == 0;
}