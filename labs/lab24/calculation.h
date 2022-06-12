#ifndef CALCULATION_H
#define CALCULATION_H
#include "token_queue.h"
#include "token_tree_stack.h"
#include "error_struct.h"
#include "sdbl.h"
#include <string.h>
#include <math.h>
double calc_prefix(queue_token *q, error *err);
double calc_postfix(queue_token *q, error *err);

#endif
