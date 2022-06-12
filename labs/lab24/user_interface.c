#include "user_interface.h"

typedef enum {
    READ_VAR_OR_FUNC_MISS,
    READ_VAR_OR_FUNC_SCAN
} read_var_or_func_state;

typedef enum {
    READ_VAR,
    READ_FUNC
} read_result_var_or_func;

typedef enum {
    READ_CONSTANT_MISS,
    READ_CONSTANT_BEFORE_POINT,
    READ_CONSTANT_AFTER_POINT
} read_constant_state;

static bool is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

static bool is_operator(char c) {
    return is_unary_op(c) || is_binary_op(c);
}

static bool is_function(char *str) {
    return is_unary_func(str) || is_binary_func(str);
}

static bool is_bracket(char c) {
    return c == '(' || c == ')';
}

static bool is_sep(char c) {
    return (('\t' <= c && c <= '\r') || c == ' ') && c != '\n';
}

static int get_min_priority_op(vector_token *v) {
    int res = 0;
    bool in_br = false;
    for (int i = 0; i < vtok_get_size(v); ++i) {
        token t = vtok_get(v, i);
        if (t.type == TOK_LBR) in_br = true;
        else if (t.type == TOK_RBR) in_br = false;
        else if (!in_br && t.type == TOK_OP && get_priority(t.op) > res)
            res = get_priority(t.op);
    }
    return res;
}

static void move_from_vector_to_queue(vector_token *from, queue_token *to) {
    while (!vtok_is_empty(from)) {
        token t = vtok_pop_front(from);
        qtok_push(to, t);
    }
}

static void push_variable_x(vector_token *coef, queue_token *infix, int power) {
    int min_pr = get_min_priority_op(coef);
    token tmp;
    tmp.type = TOK_LBR;
    if (min_pr > get_priority('*')) qtok_push(infix, tmp);
    move_from_vector_to_queue(coef, infix);
    tmp.type = TOK_RBR;
    if (min_pr > get_priority('*')) qtok_push(infix, tmp);
    if (power == 0) return;
    tmp.type = TOK_OP;
    tmp.op = '*';
    qtok_push(infix, tmp);
    tmp.type = TOK_VAR;
    strcpy(tmp.varname, "x");
    qtok_push(infix, tmp);
    if (power <= 1) return;
    tmp.type = TOK_OP;
    tmp.op = '^';
    qtok_push(infix, tmp);
    tmp.type = TOK_VAL;
    tmp.val = power;
    qtok_push(infix, tmp);
}

static read_result read_var_or_func(char *str, read_result_var_or_func *st_res, error *err) {
    int c;
    char ch;
    read_result res = READ_RESULT_CONTINUES;
    read_var_or_func_state st = READ_VAR_OR_FUNC_SCAN;
    strcpy(str, "");
    do {
        c = getchar();
        if (c == EOF || c == '\n') {
            res = READ_RESULT_END_WITH_SCAN;
            break;
        }
        if (st == READ_VAR_OR_FUNC_MISS) continue;
        ch = (char)c;
        if (strlen(str) >= MAX_LEN_VAR_AND_FUNC_NAME) {
            res = READ_RESULT_ERROR;
            st = READ_VAR_OR_FUNC_MISS;
            err->is_error = true;
            strcpy(err->error_text, "variable or function name is too long");
        }
        else if (is_alpha(ch) || is_digit(ch) || ch == '_')
            strncat(str, &ch, 1);
        else if (is_sep(ch)) {
            res = READ_RESULT_SEPARATOR;
            break;
        }
        else if (is_bracket(ch) || is_operator(ch) || ch == ',') {
            ungetc(c, stdin);
            break;
        }
        else {
            res = READ_RESULT_ERROR;
            st = READ_VAR_OR_FUNC_MISS;
            err->is_error = true;
            strcpy(err->error_text, "variable or function name contains a forbidden character: ");
            strcpy(err->error_text, strncat(err->error_text, &ch, 1));
        }
    }
    while (true);
    if (is_function(str)) *st_res = READ_FUNC;
    else *st_res = READ_VAR;
    return res;
}

static read_result read_constant(double *val, error *err) {
    int c;
    char ch;
    read_result res = READ_RESULT_CONTINUES;
    int len_after_point = 0;
    read_constant_state st = READ_CONSTANT_BEFORE_POINT;
    do {
        c = getchar();
        if (c == EOF || c == '\n') {
            res = READ_RESULT_END_WITH_SCAN;
            break;
        }
        if (st == READ_CONSTANT_MISS) continue;
        ch = (char)c;
        if (ch == '.') {
            if (st == READ_CONSTANT_BEFORE_POINT) {
                st = READ_CONSTANT_AFTER_POINT;
                continue;
            }
        }
        else if (is_digit(ch)) {
            c = c - '0';
            if (st == READ_CONSTANT_BEFORE_POINT) {
                *val = (*val)*10 + c;
            } else {
                len_after_point++;
                *val = (*val) + pow(.1, len_after_point)*c;
            }
            continue;
        }
        else if (is_sep(ch)) {
            res = READ_RESULT_SEPARATOR;
            break;
        }
        else if (is_bracket(ch) || is_operator(ch) || ch == ',') {
            ungetc(c, stdin);
            break;
        }
        res = READ_RESULT_ERROR;
        st = READ_CONSTANT_MISS;
        err->is_error = true;
        strcpy(err->error_text, "wrong value");
    }
    while (true);
    return res;
}

read_result read_next_token(token *out, token_type prev_type, error *err) {
    int c;
    char ch;
    read_result res = READ_RESULT_CONTINUES;
    do {
        c = getchar();
    } while (is_sep(c));
    if (c == EOF || c == '\n') return READ_RESULT_END_WITHOUT_SCAN;
    ch = (char)c;
    if (is_operator(ch) || is_bracket(ch) || c == ',') {
        if (c == '(')
            out->type = TOK_LBR;
        else if (c == ')')
            out->type = TOK_RBR;
        else if (c == ',')
            out->type = TOK_SEP;
        else {
            out->type = TOK_OP;
            if (ch == '-' && (prev_type == TOK_OP || prev_type == TOK_NULL || prev_type == TOK_LBR))
                out->op = '~';
            else
                out->op = ch;
        }
        c = getchar();
        if (is_sep(c)) res = READ_RESULT_SEPARATOR;
        ungetc(c, stdin);
    }
    else if (is_alpha(ch)) {
        ungetc(ch, stdin);
        char *tmp_string[MAX_LEN_VAR_AND_FUNC_NAME];
        read_result_var_or_func tmp_state;
        res = read_var_or_func((char *)tmp_string, &tmp_state, err);
        if (res != READ_RESULT_ERROR) {
            if (tmp_state == READ_VAR) {
                out->type = TOK_VAR;
                strcpy(out->varname, (char *)tmp_string);
            }
            else {
                out->type = TOK_FUNC;
                strcpy(out->func, (char *)tmp_string);
            }
        }
    }
    else if (is_digit(ch) || ch == '.') {
        ungetc(c, stdin);
        out->val = 0;
        res = read_constant(&out->val, err);
        if (res != READ_RESULT_ERROR) out->type = TOK_VAL;
    }
    else {
        res = READ_RESULT_ERROR;
        err->is_error = true;
        strcpy(err->error_text, "unknown symbol: ");
        strcpy(err->error_text, strncat(err->error_text, &ch, 1));
    }
    return res;
}

void read_expression(queue_token *infix, error *err) {
    token cur;
    cur.type = TOK_NULL;
    while (true) {
        read_result res = read_next_token(&cur, cur.type, err);
        if (res == READ_RESULT_ERROR || res == READ_RESULT_END_WITHOUT_SCAN) return;
        qtok_push(infix, cur);
        if (res == READ_RESULT_END_WITH_SCAN) return;
    }
}

int read_coefficients(queue_token *infix, error *err) {
    vector_token cur_coef;
    vtok_init(&cur_coef);
    token cur;
    cur.type = TOK_NULL;
    int degree = -1;
    while (true) {
        read_result res = read_next_token(&cur, cur.type, err);
        if (res == READ_RESULT_ERROR ||
           (res == READ_RESULT_END_WITHOUT_SCAN && vtok_is_empty(&cur_coef))) break;
        if (res != READ_RESULT_END_WITHOUT_SCAN) vtok_push_back(&cur_coef, cur);
        if (res == READ_RESULT_SEPARATOR ||
            res == READ_RESULT_END_WITH_SCAN ||
            res == READ_RESULT_END_WITHOUT_SCAN) {
            if (degree != -1) {
                cur.type = TOK_OP;
                cur.op = '+';
                qtok_push(infix, cur);
            }
            push_variable_x(&cur_coef, infix, ++degree);
            cur.type = TOK_NULL;
            if (res == READ_RESULT_END_WITH_SCAN || res == READ_RESULT_END_WITHOUT_SCAN) break;
        }
    }
    vtok_destroy(&cur_coef);
    return degree;
}

void print_tree(tree_token t, int k) {
    if (t == NULL) return;
    print_tree(t->right, k + 1);
    printf("%*s", 10*k, "");
    if (t->val.type == TOK_VAL)
        printf("%lf\n", t->val.val);
    else if (t->val.type == TOK_OP)
        if (t->val.op == '~') printf("-\n");
        else printf("%c\n", t->val.op);
    else if (t->val.type == TOK_FUNC)
        printf("%s\n", t->val.func);
    else
        printf("%s\n", t->val.varname);
    print_tree(t->left, k + 1);
}

void print_expression(queue_token infix) {
    while (!qtok_is_empty(&infix)) {
        token t = qtok_pop(&infix);
        if (t.type == TOK_VAL) printf("%lf", t.val);
        else if (t.type == TOK_VAR) printf("%s", t.varname);
        else if (t.type == TOK_OP) {
            if (t.op == '^' || t.op == '*' || t.op == '/')
                printf("%c", t.op);
            else if (t.op == '~')
                printf("-");
            else
                printf(" %c ", t.op);
        }
        else if (t.type == TOK_LBR) printf("(");
        else if (t.type == TOK_RBR) printf(")");
        else if (t.type == TOK_FUNC) printf("%s", t.func);
        else if (t.type == TOK_SEP) printf(", ");
    }
    printf("\n");
}