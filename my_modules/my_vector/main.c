//
// Created by Aprold on 14.03.2022.
//

#include <stdio.h>
#include "vdbl.h"

int main() {
    size_t size;
    scanf("%zu", &size);
    vector_dbl v;
    vdbl_init(&v, size);
    vdbl_push(&v, 4567.467);
    for (size_t i = 0; i < size; i++) {
        double tmp;
        scanf("%lf", &tmp);
        vdbl_set(&v, i, tmp);
    }
    for (size_t i = 0; i < v.size; i++) {
        printf("%lf ", vdbl_get(&v, i));
    }
    printf("\n%d", vdbl_get_size(&v));
    printf("\n%lf", vdbl_pop(&v));
    printf("\n%d", vdbl_get_size(&v));
    vdbl_destroy(&v);
    return 0;
}
