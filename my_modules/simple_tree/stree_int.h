#ifndef SIMPLE_TREE_STREE_INT_H
#define SIMPLE_TREE_STREE_INT_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct stree_node stree_node;

struct stree_node {
    int val;
    stree_node *oldest_son;
    stree_node *next_brother;
};

typedef stree_node * stree;

stree stint_create_empty();
stree stint_build(stree oldest_son, stree next_brother, int root_val);
bool stint_is_empty(stree t);
int stint_get_root_val(stree t);
stree stint_get_oldest_son(stree t);
stree stint_get_next_brother(stree t);
void stint_destroy(stree t);
void stint_destroy_rec(stree t);
stree stint_change_root_val(stree t, int new_val);

#endif //SIMPLE_TREE_STREE_INT_H
