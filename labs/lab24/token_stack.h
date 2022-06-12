#ifndef TOKEN_STACK_H
#define TOKEN_STACK_H
#include <stdbool.h>
#include <stdlib.h>
#include "token_struct.h"

typedef struct {
    size_t size;
    size_t pool_size;
    token *buf;
} stack_token;

void stok_init(stack_token *st);
void stok_destroy(stack_token *st);
bool stok_push(stack_token *st, token el);
token stok_pop(stack_token *st);
token stok_peek(stack_token *st);
bool stok_is_empty(stack_token *st);

#endif
