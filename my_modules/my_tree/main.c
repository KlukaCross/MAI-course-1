#include <stdio.h>
#include "tdbl.h"

tree build_tree(int n) {
    tree_node* t;
    if (n == 0) {
        t = NULL;
    } else {
        int nl = n/2;
        int nr = n-nl-1;
        double val;
        scanf("%lf", &val);
        t = malloc(sizeof(tree));
        t->val = val;
        t->left = build_tree(nl);
        t->right = build_tree(nr);
    }
    return t;
}

void print_tree(tree t, int n) {
    if (t == NULL) return;
    print_tree(t->right, n+1);
    printf("%*s", 2*n, "");
    printf("%lf\n", t->val);
    print_tree(t->left, n+1);
}

int main() {
    int n;
    scanf("%d", &n);
    tree t = build_tree(n);
    print_tree(t,  0);
    return 0;
}

