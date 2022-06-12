#include "file_int.h"
void fint_init(file_int *f, char * name) {
    f->size = 0;
    f->buf = fopen(name, "w+");
}

void fint_destroy(file_int *f) {
    fclose(f->buf);
    f->size = 0;
}

bool fint_push(file_int *f, int el) {
    fseek(f->buf, SEEK_SET, f->size);
    if (!fwrite(&el, sizeof(int), 1, f->buf))
        return false;
    f->size++;
    return true;
}

int fint_pop(file_int *f) {
    f->size--;
    fseek(f->buf, SEEK_SET, f->size);
    int res;
    fread(&res, sizeof(int), 1, f->buf);
    return res;
}

int fint_peek(file_int *f) {
    fseek(f->buf, SEEK_SET, f->size);
    int res;
    fread(&res, sizeof(int), 1, f->buf);
    return res;
}

int fint_get(file_int *f, int i, int el) {
    fseek(f->buf, SEEK_SET, i);
    int res;
    fread(&res, sizeof(int), 1, f->buf);
    return res;
}

bool fint_is_empty(file_int *f) {
    return f->size == 0;
}