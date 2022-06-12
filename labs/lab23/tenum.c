#include "tenum.h"

tree tnm_create_empty() {
    return NULL;
}

tree tnm_build(tree left, tree right, VILLAGES root_val) {
    tree t = malloc(sizeof(tree_node));
    t->val = root_val;
    t->left = left;
    t->right = right;
    return t;
}

bool tnm_is_empty(tree t) {
    return t == NULL;
}

VILLAGES tnm_get_root_val(tree t) {
    return t->val;
}

tree tnm_get_left(tree t) {
    return t->left;
}
tree tnm_get_right(tree t) {
    return t->right;
}

void tnm_destroy(tree t) {
    free(t);
}

void tnm_destroy_rec(tree t) {
    if (tnm_is_empty(t)) return;
    tnm_destroy_rec(tnm_get_left(t));
    tnm_destroy_rec(tnm_get_right(t));
    tnm_destroy(t);
}

tree tnm_change_root_val(tree t, VILLAGES new_val) {
    tree left = tnm_get_left(t);
    tree right = tnm_get_right(t);
    tnm_destroy(t);
    tree res = tnm_build(left, right, new_val);
    return res;
}

void tnm_bin_search_tree_add(tree *t, VILLAGES val) {
    if (*t == NULL) {
        *t = malloc(sizeof(tree));
        (*t)->left = NULL;
        (*t)->right = NULL;
        (*t)->val = val;
    } else if (val < (*t)->val) {
        tnm_bin_search_tree_add(&(*t)->left, val);
    } else if (val > (*t)->val) {
        tnm_bin_search_tree_add(&(*t)->right, val);
    }
}

void tnm_bin_search_tree_remove(tree *t) {
    if ((*t)->left == NULL && (*t)->right == NULL) {
        free(*t);
        *t = NULL;
    } else if ((*t)->right == NULL) {
        tree child = (*t)->left;
        free(*t);
        *t = child;
    } else if ((*t)->left == NULL) {
        tree child = (*t)->right;
        free(*t);
        *t = child;
    } else {
        tree *max_left = &(*t)->left;
        while ((*max_left)->right != NULL) {
            max_left = &(*max_left)->right;
        }
        tree tmp = *max_left;
        *max_left = (*max_left)->left;
        tmp->left = (*t)->left;
        tmp->right = (*t)->right;
        free(*t);
        *t = tmp;
    }
}

tree* tnm_find_element(tree *t, VILLAGES val) {
    if (*t == NULL) return NULL;
    else if (val == (*t)->val)
        return t;
    else if (val < (*t)->val)
        return tnm_find_element(&(*t)->left, val);
    else
        return tnm_find_element(&(*t)->right, val);
}

int tnm_height(tree t) {
    if (t == NULL) return 0;
    int left = tnm_height(t->left);
    int right = tnm_height(t->right);
    return ((left>right) ? left : right) + 1;
}
