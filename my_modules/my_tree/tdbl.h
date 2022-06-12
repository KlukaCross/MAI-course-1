#ifndef MY_TREE_TDBL_H
#define MY_TREE_TDBL_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct tree_node tree_node;

struct tree_node {
    double val;
    tree_node *left;
    tree_node *right;
};

typedef tree_node * tree;

tree create_empty();
tree build(tree left, tree right, double root_val);
bool is_empty(tree t);
double get_root_val(tree t);
tree get_left(tree t);
tree get_right(tree t);
void destroy(tree t);
void destroy_rec(tree t);
tree change_root_val(tree t, double new_val);
void bin_search_tree_add(tree *t, double val);
void bin_search_tree_remove(tree *t);
tree *find_element(tree *t, double val);

#endif //MY_TREE_TDBL_H
