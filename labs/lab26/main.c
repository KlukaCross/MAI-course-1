#include <stdio.h>
#include "list.h"

typedef enum {
    STATE_FIND_DIGIT,
    STATE_SCAN
} state;

bool shift_first_min(barrier_list *lst) {
    if (list_get_size(lst) <= 1) return false;
    list_iter iter = list_iter_begin(lst);
    int prev_num = list_iter_get(&iter);
    list_iter_move_next(&iter);
    for (; !list_iter_equal(iter, list_iter_end(lst)); list_iter_move_next(&iter)) {
        if (prev_num > list_iter_get(&iter)) break;
        else prev_num = list_iter_get(&iter);
    }
    if (list_iter_equal(iter, list_iter_end(lst))) return false;
    int shift_num = list_iter_get(&iter);
    list_iter_remove(&iter);
    list_iter_move_back(&iter);
    for (; !list_iter_equal(iter, list_iter_end(lst)); list_iter_move_back(&iter)) {
        if (list_iter_get(&iter) < shift_num) break;
    }
    list_iter_move_next(&iter);
    list_iter_insert_before(&iter, shift_num);
    return true;
}

void sort(barrier_list *lst) {
    while (shift_first_min(lst));
}

bool is_sep(int ch) {
    return (('\t' <= ch && ch <= '\r') || ch == ' ');
}

int main() {
    barrier_list lst;
    list_init(&lst);
    list_iter iter = list_iter_begin(&lst);
    int n = 0;
    int s;
    state st = STATE_FIND_DIGIT;
    do {
        s = getchar();
        if (s == EOF || s == '\n') continue;
        if (is_sep(s) && st == STATE_SCAN) {
            list_iter_insert_before(&iter, n);
            n = 0;
            st = STATE_FIND_DIGIT;
        } else if (!is_sep(s)) {
            n = n*10 + (s-'0');
            st = STATE_SCAN;
        }
    }
    while (s != EOF && s != '\n');
    if (st == STATE_SCAN) list_iter_insert_before(&iter, n);
    sort(&lst);
    for (iter = list_iter_begin(&lst); !list_iter_equal(iter, list_iter_end(&lst)); list_iter_move_next(&iter)) {
        printf("%d ", list_iter_get(&iter));
    }
    printf("\n");
    list_destroy(&lst);
    return 0;
}
