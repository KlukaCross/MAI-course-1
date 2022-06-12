#include <stdlib.h>
#include "vdbl.h"

bool vdbl_init(vector_dbl *v, size_t size) {
    v->size = size;
    v->buf = malloc(size*sizeof(double));
    if (v->buf == NULL) {
        v->size = 0;
        return false;
    }
    for (size_t i = 0; i < v->size; ++i) {
        vdbl_set(v, i, 0);
    }
    return true;
}

void vdbl_destroy(vector_dbl *v) {
    free(v->buf);
    v->buf = NULL;
    v->size = 0;
}

size_t vdbl_get_size(vector_dbl *v) {
    return v->size;
}

bool vdbl_set_size(vector_dbl *v, size_t newsize) {
    double *v2 = realloc(v->buf, newsize*sizeof(double));
    if (v2 == NULL) return false;
    v->buf = v2;
    if (newsize > v->size) {
        for (size_t i = v->size; i < newsize; ++i) {
            vdbl_set(v, i, 0);
        }
    }
    v->size = newsize;
    return true;
}

double vdbl_get(vector_dbl *v, size_t i) {
    return v->buf[i];
}

void vdbl_set(vector_dbl *v, size_t i, double newval) {
    v->buf[i] = newval;
}

bool vdbl_push(vector_dbl *v, double newval) {
    bool ans = vdbl_set_size(v, v->size+1);
    if (!ans) return false;
    vdbl_set(v, v->size-1, newval);
    return true;
}

double vdbl_pop(vector_dbl *v) {
    double val = vdbl_get(v, v->size-1);
    bool ans = vdbl_set_size(v, v->size-1);
    if (!ans) return false;
    return val;
}
