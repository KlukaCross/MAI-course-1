#include "calculation.h"
#include "token_struct.h"

static double calc_unary_op(char op, double operand, error *err) {
    if (op == '~') return -operand;
    err->is_error = true;
    strcpy(err->error_text, strcat("unknown unary operator ", &op));
    return 0;
}

static double calc_binary_op(char op, double left, double right, error *err) {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '^': return pow(left, right);
        case '/': {
            if (right == 0) {
                err->is_error = true;
                strcpy(err->error_text, "division by zero");
                return 0;
            } return left / right;
        }
        default: {
            err->is_error = true;
            strcpy(err->error_text, strcat("unknown binary operator: ", &op));
            return 0;
        }
    }
}

static double calc_unary_func(char* func, double arg, error *err) {
    if (!strcmp(func, "sin")) return sin(arg);
    if (!strcmp(func, "cos")) return cos(arg);
    err->is_error = true;
    strcpy(err->error_text, strcat("unknown unary function: ", func));
    return 0;
}

static double calc_binary_func(char* func, double arg1, double arg2, error *err) {
    if (!strcmp(func, "max")) return (arg1>=arg2)? arg1 : arg2;
    if (!strcmp(func, "min")) return (arg1<=arg2)? arg1 : arg2;
    err->is_error = true;
    strcpy(err->error_text, strcat("unknown binary function: ", func));
    return 0;
}

double calc_prefix(queue_token *q, error *err) {
    token t = qtok_pop(q);
    if (t.type == TOK_VAL || t.type == TOK_VAR)
        return t.val;

    if ((t.type == TOK_OP && is_unary_op(t.op)) ||
        (t.type == TOK_FUNC && is_unary_func(t.func))) {
        double operand = calc_prefix(q, err);
        if (err->is_error) return 0;
        return (t.type == TOK_OP)? calc_unary_op(t.op, operand, err) :
        calc_unary_func(t.func, operand, err);
    }
    double operand1 = calc_prefix(q, err);
    double operand2 = calc_prefix(q, err);
    if (err->is_error) return 0;
    return (t.type == TOK_OP)? calc_binary_op(t.op, operand1, operand2, err) :
    calc_binary_func(t.func, operand1, operand2, err);
}

