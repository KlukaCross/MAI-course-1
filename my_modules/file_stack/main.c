#include "sdbl.h"

int main() {
    stack_dbl st;
    sdbl_init(&st, "test.txt");
    sdbl_push(&st, 1);
    sdbl_push(&st, 2);
    sdbl_push(&st, 3);
    double a = sdbl_pop(&st);
    a = sdbl_pop(&st);
    sdbl_push(&st, 4);
    a = sdbl_pop(&st);
    a = sdbl_peek(&st);
    return 0;
}
