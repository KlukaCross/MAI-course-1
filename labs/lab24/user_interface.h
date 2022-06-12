#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "token_struct.h"
#include "token_queue.h"
#include "error_struct.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "token_tree.h"
#include "token_vector.h"

typedef enum {
    READ_RESULT_END_WITH_SCAN,
    READ_RESULT_END_WITHOUT_SCAN,
    READ_RESULT_CONTINUES,
    READ_RESULT_SEPARATOR,
    READ_RESULT_ERROR
} read_result;

read_result read_next_token(token *out, token_type prev_type, error *err);
void read_expression(queue_token *infix, error *err);
int read_coefficients(queue_token *infix, error *err);
void print_tree(tree_token t, int k);
void print_expression(queue_token infix);

#endif
