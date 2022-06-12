#ifndef BUILDING_H
#define BUILDING_H
#include "token_queue.h"
#include "token_tree_stack.h"
#include "error_struct.h"

void build_tree(queue_token *postfix, tree_token *tree, error *err);
void build_union_tree(tree_token tree1, tree_token tree2, tree_token *union_tree, token union_func, int polynom_degree, int k);
void build_postfix(tree_token tree, queue_token *postfix);
void build_infix(tree_token tree, queue_token *buf, int *min_pr);

#endif
