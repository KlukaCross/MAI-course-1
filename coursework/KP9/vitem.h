#ifndef _VECTOR_VITEM_H
#define _VECTOR_VITEM_H
#include <stdbool.h>
#include <stdlib.h>
#include "item.h"

typedef struct {
    item *buf;
    size_t pool_size;
    size_t first;
    size_t size;
} vector_item;

void vitem_init(vector_item *v);
void vitem_destroy(vector_item *v);

size_t vitem_get_size(vector_item *v);
bool vitem_set_size(vector_item *v, size_t new_size);

bool vitem_push_front(vector_item *v, item val);
bool vitem_push_back(vector_item *v, item val);
item vitem_pop_front(vector_item *v);
item vitem_pop_back(vector_item *v);

item vitem_get(vector_item *v, size_t i);
void vitem_set(vector_item *v, size_t i, item val);

item vitem_get_front(vector_item *v);
item vitem_get_back(vector_item *v);

bool vitem_is_empty(vector_item *v);

void vitem_swap(vector_item *v, int i, int j);

int vitem_bin_search_key(vector_item *v, __complex128 key);

#endif
