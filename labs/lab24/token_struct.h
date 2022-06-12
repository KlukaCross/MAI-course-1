#ifndef TOKEN_STRUCT_H
#define TOKEN_STRUCT_H

#include <string.h>
#include <stdbool.h>

#define MAX_LEN_VAR_AND_FUNC_NAME 64

typedef enum {
    TOK_NULL,
    TOK_OP,
    TOK_VAL,
    TOK_VAR,
    TOK_LBR,
    TOK_RBR,
    TOK_FUNC,
    TOK_SEP
} token_type;

typedef struct {
    token_type type;
    char op;
    double val;
    char varname[MAX_LEN_VAR_AND_FUNC_NAME];
    char func[MAX_LEN_VAR_AND_FUNC_NAME];
} token;

extern const char *UNARY_FUNCTIONS[];
extern const char *BINARY_FUNCTIONS[];
extern const char *UNARY_OPERATORS;
extern const char *BINARY_OPERATORS;
extern const char *LEFT_ASSOCIATIVE_OPERATORS;
extern const char *RIGHT_ASSOCIATIVE_OPERATORS;

extern const int SIZE_UNARY_FUNCTIONS;
extern const int SIZE_BINARY_FUNCTIONS;

bool is_unary_op(char op);
bool is_binary_op(char op);
bool is_unary_func(char *func);
bool is_binary_func(char *func);
bool is_left_op(char op);
int get_priority(char op);

#endif
