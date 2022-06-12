#include "tdbl.h"

tree create_empty() {
    return NULL;
}

tree build(tree left, tree right, double root_val) {
    tree t = malloc(sizeof(tree_node));
    t->val = root_val;
    t->left = left;
    t->right = right;
    return t;
}

bool is_empty(tree t) {
    return t == NULL;
}

double get_root_val(tree t) {
    return t->val;
}

tree get_left(tree t) {
    return t->left;
}
tree get_right(tree t) {
    return t->right;
}

void destroy(tree t) {
    free(t);
}

void destroy_rec(tree t) {
    if (is_empty(t)) return;
    destroy_rec(get_left(t));
    destroy_rec(get_right(t));
    destroy(t);
}

tree change_root_val(tree t, double new_val) {
    tree left = get_left(t);
    tree right = get_right(t);
    destroy(t);
    tree res = build(left, right, new_val);
    return res;
}

void bin_search_tree_add(tree *t, double val) {
    if (*t == NULL) {
        *t = malloc(sizeof(tree));
        (*t)->left = NULL;
        (*t)->right = NULL;
        (*t)->val = val;
    } else if (val < (*t)->val) {
        bin_search_tree_add(&(*t)->left, val);
    } else if (val > (*t)->val) {
        bin_search_tree_add(&(*t)->right, val);
    }
}

void bin_search_tree_remove(tree *t) {
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

tree* find_element(tree *t, double val) {
    if (*t == NULL) return NULL;
    else if (val == (*t)->val)
        return t;
    else if (val < (*t)->val)
        return find_element(&(*t)->left, val);
    else
        return find_element(&(*t)->right, val);
}

