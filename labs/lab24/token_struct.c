#include "token_struct.h"

const char *UNARY_FUNCTIONS[] = {"sin", "cos"};
const char *BINARY_FUNCTIONS[] = {"max", "min"};
const char *UNARY_OPERATORS = "~";
const char *BINARY_OPERATORS = "+-*/^";
const char *LEFT_ASSOCIATIVE_OPERATORS = "+-*/";
const char *RIGHT_ASSOCIATIVE_OPERATORS = "~^";

const int SIZE_UNARY_FUNCTIONS = sizeof(UNARY_FUNCTIONS) / sizeof(UNARY_FUNCTIONS[0]);
const int SIZE_BINARY_FUNCTIONS = sizeof(BINARY_FUNCTIONS)/sizeof(BINARY_FUNCTIONS[0]);

bool is_unary_op(char op) {
    for (int i = 0; i < strlen(UNARY_OPERATORS); ++i) {
        if (!strncmp(&UNARY_OPERATORS[i], &op, 1)) return true;
    }
    return false;
}

bool is_binary_op(char op) {
    for (int i = 0; i < strlen(BINARY_OPERATORS); ++i) {
        if (!strncmp(&BINARY_OPERATORS[i], &op, 1)) return true;
    }
    return false;
}

bool is_unary_func(char *func) {
    for (int i = 0; i < SIZE_UNARY_FUNCTIONS; ++i) {
        if (!strcmp(UNARY_FUNCTIONS[i], func)) return true;
    }
    return false;
}

bool is_binary_func(char *func) {
    for (int i = 0; i < SIZE_BINARY_FUNCTIONS; ++i) {
        if (!strcmp(BINARY_FUNCTIONS[i], func)) return true;
    }
    return false;
}

bool is_left_op(char op) {
    for (int i = 0; i < strlen(LEFT_ASSOCIATIVE_OPERATORS); ++i) {
        if (!strncmp(&LEFT_ASSOCIATIVE_OPERATORS[i], &op, 1)) return true;
    }
    return false;
}

int get_priority(char op) {
    if (op == '~') return 1;
    if (op == '^') return 2;
    if (op == '*' || op == '/') return 3;
    if (op == '+' || op == '-') return 4;
    return -1;
}
