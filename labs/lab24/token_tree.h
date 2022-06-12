#ifndef TOKEN_TREE_H
#define TOKEN_TREE_H
#include <stdbool.h>
#include <stdlib.h>
#include "token_struct.h"

typedef struct tree_token_node tree_token_node;

struct tree_token_node {
    token val;
    tree_token_node *left;
    tree_token_node *right;
};

typedef tree_token_node* tree_token;

tree_token ttok_create_empty();
tree_token ttok_build(tree_token left, tree_token right, token root_val);
bool ttok_is_empty(tree_token t);
token ttok_get_root_val(tree_token t);
tree_token ttok_get_left(tree_token t);
tree_token ttok_get_right(tree_token t);
void ttok_destroy(tree_token t);
void ttok_destroy_rec(tree_token t);
tree_token ttok_change_root_val(tree_token t, token new_val);
void ttok_bin_search_tree_remove(tree_token *t);
void ttok_copy(tree_token from, tree_token *to);

#endif
