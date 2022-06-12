#ifndef TOKEN_VECTOR_H
#define TOKEN_VECTOR_H
#include <stdbool.h>
#include <stdlib.h>
#include "token_struct.h"

typedef struct {
    token *buf;
    size_t pool_size;
    size_t first;
    size_t size;
} vector_token;

void vtok_init(vector_token *v);
void vtok_destroy(vector_token *v);

size_t vtok_get_size(vector_token *v);
bool vtok_set_size(vector_token *v, size_t new_size);

bool vtok_push_front(vector_token *v, token val);
bool vtok_push_back(vector_token *v, token val);
token vtok_pop_front(vector_token *v);
token vtok_pop_back(vector_token *v);

token vtok_get(vector_token *v, size_t i);
void vtok_set(vector_token *v, size_t i, token val);

token vtok_get_front(vector_token *v);
token vtok_get_back(vector_token *v);

bool vtok_is_empty(vector_token *v);

#endif
