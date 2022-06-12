#include "token_tree.h"

tree_token ttok_create_empty() {
    return NULL;
}

tree_token ttok_build(tree_token left, tree_token right, token root_val) {
    tree_token t = malloc(sizeof(tree_token_node));
    t->val = root_val;
    t->left = left;
    t->right = right;
    return t;
}

bool ttok_is_empty(tree_token t) {
    return t == NULL;
}

token ttok_get_root_val(tree_token t) {
    return t->val;
}

tree_token ttok_get_left(tree_token t) {
    return t->left;
}
tree_token ttok_get_right(tree_token t) {
    return t->right;
}

void ttok_destroy(tree_token t) {
    free(t);
}

void ttok_destroy_rec(tree_token t) {
    if (ttok_is_empty(t)) return;
    ttok_destroy_rec(ttok_get_left(t));
    ttok_destroy_rec(ttok_get_right(t));
    ttok_destroy(t);
}

tree_token ttok_change_root_val(tree_token t, token new_val) {
    tree_token left = ttok_get_left(t);
    tree_token right = ttok_get_right(t);
    ttok_destroy(t);
    tree_token res = ttok_build(left, right, new_val);
    return res;
}

void ttok_bin_search_tree_remove(tree_token *t) {
    if ((*t)->left == NULL && (*t)->right == NULL) {
        free(*t);
        *t = NULL;
    } else if ((*t)->right == NULL) {
        tree_token child = (*t)->left;
        free(*t);
        *t = child;
    } else if ((*t)->left == NULL) {
        tree_token child = (*t)->right;
        free(*t);
        *t = child;
    } else {
        tree_token *max_left = &(*t)->left;
        while ((*max_left)->right != NULL) {
            max_left = &(*max_left)->right;
        }
        tree_token tmp = *max_left;
        *max_left = (*max_left)->left;
        tmp->left = (*t)->left;
        tmp->right = (*t)->right;
        free(*t);
        *t = tmp;
    }
}

void ttok_copy(tree_token from, tree_token *to) {
    if (ttok_is_empty(from)) return;
    tree_token left = ttok_create_empty();
    tree_token right = ttok_create_empty();
    ttok_copy(ttok_get_left(from), &left);
    ttok_copy(ttok_get_right(from), &right);
    *to = ttok_build(left, right, ttok_get_root_val(from));
}
