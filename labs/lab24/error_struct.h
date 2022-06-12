#ifndef ERROR_STRUCT_H
#define ERROR_STRUCT_H
#include <stdbool.h>

typedef struct {
    bool is_error;
    char error_text[128];
} error;

#endif
