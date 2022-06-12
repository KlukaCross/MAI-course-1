#include <stdio.h>
#include "stree_int.h"

int main() {
    stree son2 = stint_build(NULL, NULL, 2);
    stree son1 = stint_build(NULL, son2, 1);
    stree son3 = stint_build(NULL, NULL, 2);
    stree dad_bro = stint_build(son3, NULL, 4);
    stree dad = stint_build(son1, dad_bro, 5);
    stint_destroy_rec(dad);
    return 0;
}
