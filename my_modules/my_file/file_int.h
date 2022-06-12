#ifndef MY_FILE_FILE_INT_H
#define MY_FILE_FILE_INT_H
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    size_t size;
    FILE *buf;
} file_int;

void fint_init(file_int *f, char * name);
void fint_destroy(file_int *f);
bool fint_push(file_int *f, int el);
int fint_pop(file_int *f);
int fint_peek(file_int *f);
int fint_get(file_int *f, int i, int el);
bool fint_is_empty(file_int *f);

#endif //MY_FILE_FILE_INT_H
