#include "sdbl.h"

void sdbl_init(stack_dbl *st, char * name) {
    st->size = 0;
    st->buf = fopen(name, "w+");
}

void sdbl_destroy(stack_dbl *st) {
    st->size = 0;
    fclose(st->buf);
}

bool sdbl_push(stack_dbl *st, double el) {
    if (fseek(st->buf, st->size*sizeof(double), SEEK_SET)) return false;
    if (!fwrite(&el, sizeof(double), 1, st->buf)) return false;
    st->size++;
    return true;
}

double sdbl_pop(stack_dbl *st) {
    double res;
    fseek(st->buf, (st->size-1)*sizeof(double), SEEK_SET);
    fread(&res, sizeof(double), 1, st->buf);
    st->size--;
    return res;
}

double sdbl_peek(stack_dbl *st) {
    double res;
    fseek(st->buf, (st->size-1)*sizeof(double), SEEK_SET);
    fread(&res, sizeof(double), 1, st->buf);
    return res;
}

bool stdbl_is_empty(stack_dbl *st) {
    return st->size == 0;
}
