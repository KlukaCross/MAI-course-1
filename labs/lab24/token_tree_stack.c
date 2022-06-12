#include "token_tree_stack.h"

static bool grow_buffer(stack_tree_token *st) {
    size_t new_size = st->pool_size * 2;
    if (st->pool_size == 0) new_size = 4;
    tree_token *new_buf = realloc(st->buf, new_size * sizeof(tree_token));
    if (new_buf == NULL) return false;
    st->buf = new_buf;
    st->pool_size = new_size;
    return true;
}

void stt_init(stack_tree_token *st) {
    st->size = 0;
    st->buf = NULL;
    st->pool_size = 0;
}

void stt_destroy(stack_tree_token *st) {
    st->size = 0;
    st->pool_size = 0;
    free(st->buf);
    st->buf = NULL;
}

bool stt_push(stack_tree_token *st, tree_token el) {
    if (st->size >= st->pool_size) {
        if (!grow_buffer(st)) return false;
    }
    st->buf[st->size] = el;
    st->size++;
    return true;
}

tree_token stt_pop(stack_tree_token *st) {
    tree_token res = st->buf[st->size - 1];
    st->size--;
    if (st->size * 4 == st->pool_size) {
        st->pool_size = st->pool_size / 2;
        st->buf = realloc(st->buf, st->pool_size * sizeof(tree_token));
    }
    return res;
}

tree_token stt_peek(stack_tree_token *st) {
    return st->buf[st->size-1];
}

bool stt_is_empty(stack_tree_token *st) {
    return st->size == 0;
}
