#ifndef TDBL_H
#define TDBL_H

#include <stdbool.h>
#include <stdlib.h>
#include "villages.h"

typedef struct tree_node tree_node;

struct tree_node {
    VILLAGES val;
    tree_node *left;
    tree_node *right;
};

typedef tree_node * tree;

tree tnm_create_empty();
tree tnm_build(tree left, tree right, VILLAGES root_val);
bool tnm_is_empty(tree t);
VILLAGES tnm_get_root_val(tree t);
tree tnm_get_left(tree t);
tree tnm_get_right(tree t);
void tnm_destroy(tree t);
void tnm_destroy_rec(tree t);
tree tnm_change_root_val(tree t, VILLAGES new_val);
void tnm_bin_search_tree_add(tree *t, VILLAGES val);
void tnm_bin_search_tree_remove(tree *t);
tree *tnm_find_element(tree *t, VILLAGES val);
int tnm_height(tree t);

#endif
