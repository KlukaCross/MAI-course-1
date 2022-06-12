#ifndef _ITEM_H
#define _ITEM_H
#define MAX_LEN_VALUE 1024
#include <quadmath.h>

typedef struct {
    __complex128 key;
    char val[MAX_LEN_VALUE];
} item;

int key_cmp(__complex128 key1, __complex128 key2);

#endif
