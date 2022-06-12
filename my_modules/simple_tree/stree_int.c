#include "stree_int.h"

stree stint_create_empty() {
    return NULL;
}

stree stint_build(stree oldest_son, stree next_brother, int root_val) {
    stree t = malloc(sizeof(stree_node));
    t->val = root_val;
    t->oldest_son = oldest_son;
    t->next_brother = next_brother;
    return t;
}

bool stint_is_empty(stree t) {
    return t == NULL;
}

int stint_get_root_val(stree t) {
    return t->val;
}

stree stint_get_oldest_son(stree t) {
    return t->oldest_son;
}
stree stint_get_next_brother(stree t) {
    return t->next_brother;
}

void stint_destroy(stree t) {
    free(t);
}

void stint_destroy_rec(stree t) {
    if (stint_is_empty(t)) return;
    stint_destroy_rec(stint_get_oldest_son(t));
    stint_destroy_rec(stint_get_next_brother(t));
    stint_destroy(t);
}

stree stint_change_root_val(stree t, int new_val) {
    stree next_brother = stint_get_next_brother(t);
    stree oldest_son = stint_get_oldest_son(t);
    stint_destroy(t);
    stree res = stint_build(oldest_son, next_brother, new_val);
    return res;
}
