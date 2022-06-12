#include <stdio.h>
#include "svdbl.h"

void print_v(svector_dbl *v) {
    for (size_t i = 0; i < v->size; i++) {
        printf("%lf ", svdbl_get(v, i));
    }
    printf("\n");
}

int main() {
    svector_dbl v;
    svdbl_init(&v);
    svdbl_push_back(&v, 1);
    svdbl_push_back(&v, 2);
    svdbl_push_back(&v, 3);
    svdbl_pop_front(&v);
    svdbl_pop_front(&v);
    svdbl_pop_front(&v);
    svdbl_push_back(&v, 4);
    printf("%lf\n", svdbl_pop_back(&v));
    /*
    print_v(&v);
    svdbl_pop_front(&v);
    print_v(&v);
    svdbl_set_size(&v, 10);
    print_v(&v);
    svdbl_set(&v, 9, 99);
    print_v(&v);
    printf("%lf\n", svdbl_pop_back(&v));
    print_v(&v);
    svdbl_pop_front(&v);
    svdbl_pop_front(&v);
    svdbl_push_front(&v, 100);
    svdbl_push_back(&v, 100);
    print_v(&v);
    svdbl_pop_front(&v);
    print_v(&v);
    svdbl_pop_front(&v);
    print_v(&v);
    svdbl_pop_front(&v);
    print_v(&v);
    svdbl_pop_front(&v);
    print_v(&v);
    svdbl_pop_front(&v);
    print_v(&v);
    svdbl_pop_front(&v);
    print_v(&v);
    //svdbl_push_back(&v, 1);
    //svdbl_push_front(&v, 1);
    //print_v(&v);
    //svdbl_push_back(&v, 2);
    //print_v(&v);
    //svdbl_push_front(&v, 2);
    //print_v(&v);
    //svdbl_push_back(&v, 3);
    //print_v(&v);
    //svdbl_push_front(&v, 3);
    //print_v(&v);
    //svdbl_push_back(&v, 4);
    //print_v(&v);
    //svdbl_push_front(&v, 4);
    //print_v(&v);
//
    //svdbl_pop_back(&v);
    //print_v(&v);
    //svdbl_pop_front(&v);
    //print_v(&v);
    //svdbl_pop_back(&v);
    //print_v(&v);
    //svdbl_pop_front(&v);
    //print_v(&v);
    //svdbl_pop_back(&v);
    //print_v(&v);
    //svdbl_pop_front(&v);
    //print_v(&v);
    //svdbl_pop_back(&v);
    //print_v(&v);
    //svdbl_pop_front(&v);
    //print_v(&v);
*/

    svdbl_destroy(&v);
    return 0;
}
