#include "list.h"
#include <stdio.h>

void print_list(barrier_list *lst) {
    list_iter it = list_iter_begin(lst);
    while(!list_iter_equal(it, list_iter_end(lst))) {
        printf("%lf ", list_iter_get(&it));
        list_iter_move_next(&it);
    }
    printf("\n");
}

int main() {
    barrier_list lst;
    list_init(&lst);
    list_iter it = list_iter_begin(&lst);
    list_iter_insert_before(&it, 1);
    list_iter_insert_before(&it, 2);
    list_iter_insert_before(&it, 3);
    list_iter_insert_before(&it, 4);
    list_iter_insert_before(&it, 5);
    print_list(&lst);
    list_destroy(&lst);
    print_list(&lst);
    return 0;
}
