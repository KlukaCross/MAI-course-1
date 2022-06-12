#include "sdbl.h"

int main() {
    stack_dbl st;
    sdbl_init(&st);
    sdbl_push(&st, 42);
    double a = sdbl_pop(&st);
    sdbl_push(&st, 1);
    sdbl_push(&st, 2);
    sdbl_push(&st, 3);
    sdbl_destroy(&st);
    return 0;
}
