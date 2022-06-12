#ifndef TOKEN_QUEUE_H
#define TOKEN_QUEUE_H
#include <stdbool.h>
#include <stdlib.h>
#include "token_struct.h"

typedef struct {
    size_t size;
    size_t pool_size;
    size_t first;
    token *buf;
} queue_token;

void qtok_init(queue_token *q);
void qtok_destroy(queue_token *q);
bool qtok_push(queue_token *q, token el);
token qtok_pop(queue_token *q);
token qtok_peek(queue_token *q);
bool qtok_is_empty(queue_token *q);
int qtok_get_size(queue_token *q);
void qtok_copy(queue_token *from, queue_token *to);
void qtok_move(queue_token *from, queue_token *to);

#endif
