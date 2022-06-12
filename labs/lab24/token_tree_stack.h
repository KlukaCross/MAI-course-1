#ifndef TOKEN_TREE_STACK_H
#define TOKEN_TREE_STACK_H
#include <stdbool.h>
#include <stdlib.h>
#include "token_tree.h"

typedef struct {
    size_t size;
    size_t pool_size;
    tree_token *buf;
} stack_tree_token;

void stt_init(stack_tree_token *st);
void stt_destroy(stack_tree_token *st);
bool stt_push(stack_tree_token *st, tree_token el);
tree_token stt_pop(stack_tree_token *st);
tree_token stt_peek(stack_tree_token *st);
bool stt_is_empty(stack_tree_token *st);

#endif
