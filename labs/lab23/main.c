#include <stdio.h>
#include <string.h>
#include "tenum.h"
#define MAX_LEN_STR 15

typedef enum {
    STATE_SCAN,
    STATE_SCAN_ADD,
    STATE_SCAN_DEL,
    STATE_MISS
} state;

typedef struct {
    tree t;
    int k;
} tree_level;

VILLAGES parse_value(char *s) {
    for (int i = 0; i != VILLAGE_0; ++i) {
        if (!strcmp(NAMES_VILLAGES[i], s)) return (VILLAGES)i;
    }
    return -1;
}

const char* format_value(VILLAGES val) {
    return NAMES_VILLAGES[val];
}

void print_tree(tree t, int k) {
    if (t == NULL) return;
    print_tree(t->right, k + 1);
    printf("%*s", 9*k, "");
    printf("%s\n", format_value(t->val));
    print_tree(t->left, k + 1);
}

tree_level get_min_tree_level(tree_level tl) {
    if (tnm_is_empty(tl.t)) return tl;
    tree_level left = get_min_tree_level((tree_level){tnm_get_left(tl.t), tl.k + 1});
    tree_level right = get_min_tree_level((tree_level){tnm_get_right(tl.t), tl.k + 1});
    if (tnm_is_empty(left.t) && tnm_is_empty(right.t)) return tl;
    if (tnm_is_empty(left.t) && !tnm_is_empty(right.t)) return right;
    if (!tnm_is_empty(left.t) && tnm_is_empty(right.t)) return left;
    return (left.k>right.k) ? right : left;
}

bool scan_vil(char *s, VILLAGES *vl) {
    (*vl) = parse_value(s);
    if ((*vl) == -1) {
        printf("wrong argument\n");
        return false;
    }
    return true;
}

void print_help() {
    printf("h, help - output help\n"
           "all - print available names of villages\n"
           "add VIL - add VIL to the tree\n"
           "show - print the tree\n"
           "del VIL - delete VIL from the tree\n"
           "min - print value the terminal vertex having the minimum depth\n"
           "exit - exit the program\n");
}

void execute_all() {
    for (int i = 0; i != VILLAGE_0; ++i) {
        printf("%s ", NAMES_VILLAGES[i]);
    }
    printf("\n");
}

void execute_add(char *s, tree *t) {
    VILLAGES vl;
    if (!scan_vil(s, &vl)) return;
    tnm_bin_search_tree_add(t, vl);
}

void execute_show(tree t) {
    if (tnm_is_empty(t)) printf("tree is empty");
    else print_tree(t, 0);
    printf("\n");
}

void execute_del(char *s, tree *t) {
    VILLAGES vl;
    if (!scan_vil(s, &vl)) return;
    tree *el = tnm_find_element(t, vl);
    if (el == NULL) {
        printf("this value is not in the tree\n");
        return;
    }
    tnm_bin_search_tree_remove(el);
}

void execute_min(tree t) {
    if (tnm_is_empty(t)) printf("tree is empty\n");
    else printf("%s\n", format_value(tnm_get_root_val(get_min_tree_level((tree_level){t, 0}).t)));
}

bool is_sep(char ch) {
    return (('\t' <= ch && ch <= '\r') || ch == ' ');
}

void break_str(char *str, state* st) {
    str[0] = '\0';
    *st = STATE_SCAN;
}

void conc_str(char *str, char ch) {
    int l = strlen(str);
    if (l < MAX_LEN_STR) {
        str[l+1] = '\0';
        str[l] = ch;
    }
}

void print_wrong_argument() {
    printf("wrong command\n");
}

void loop(tree *t) {
    char str[MAX_LEN_STR] = "";
    state st = STATE_SCAN;
    int s;
    char ch;
    do {
        s = getchar();
        if (s != EOF) ch = s;
        else continue;
        if (st == STATE_MISS) {
            if (ch == '\n') {
                break_str(str, &st);
                print_wrong_argument();
            }
        }
        else if (ch == '\n') {
            if (st == STATE_SCAN_ADD)
                execute_add(str, t);
            else if (st == STATE_SCAN_DEL)
                execute_del(str, t);
            else if (!strcmp(str, "h") || !strcmp(str, "help"))
                print_help();
            else if(!strcmp(str, "all"))
                execute_all();
            else if (!strcmp(str, "show"))
                execute_show(*t);
            else if (!strcmp(str, "min"))
                execute_min(*t);
            else if (!strcmp(str, "exit"))
                return;
            else if (strlen(str) != 0)
                print_wrong_argument();
            break_str(str, &st);
        }
        else if (!is_sep(ch)) {
            conc_str(str, ch);
        }
        else {
            if (!strcmp(str, "add")) {
                st = STATE_SCAN_ADD;
                str[0] = '\0';
            }
            else if (!strcmp(str, "del")) {
                st = STATE_SCAN_DEL;
                str[0] = '\0';
            }
        }
    }
    while (s != EOF);
}

int main() {
    tree t = tnm_create_empty();
    print_help();
    loop(&t);
    tnm_destroy_rec(t);
    t = NULL;
    return 0;
}
