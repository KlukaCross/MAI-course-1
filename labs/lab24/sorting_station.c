#include "sorting_station.h"
#include "token_struct.h"

static void err_miss_lbr(error *err) {
    err->is_error = true;
    strcpy(err->error_text, "opening bracket is missing");
}

static void err_miss_rbr(error *err) {
    err->is_error = true;
    strcpy(err->error_text, "closing bracket is missing");
}

static bool check_token(token_type prev, token cur) {
    if (cur.type == TOK_OP) {
        if (is_unary_op(cur.op)) {
            if (prev == TOK_FUNC) return false;
        }
        else if (prev == TOK_LBR ||
            prev == TOK_OP ||
            prev == TOK_FUNC) return false;
    } else if (cur.type == TOK_LBR) {
        if (prev == TOK_VAR ||
            prev == TOK_VAL ||
            prev == TOK_RBR) return false;
    } else if (cur.type == TOK_RBR) {
        if (prev == TOK_OP ||
            prev == TOK_LBR ||
            prev == TOK_FUNC ||
            prev == TOK_SEP) return false;
    } else if (cur.type == TOK_VAL || cur.type == TOK_VAR) {
        if (prev == TOK_VAL ||
            prev == TOK_VAR ||
            prev == TOK_RBR ||
            prev == TOK_FUNC) return false;
    } else if (cur.type == TOK_FUNC) {
        if (prev == TOK_VAL ||
            prev == TOK_VAR ||
            prev == TOK_RBR) return false;
    } else if (cur.type == TOK_SEP) {
        if (prev == TOK_OP ||
            prev == TOK_FUNC ||
            prev == TOK_NULL ||
            prev == TOK_SEP) return false;
    }
    return true;
}

static bool pop_to_lbr(stack_token *st, queue_token *postfix, error *err) {
    if (stok_is_empty(st)) {
        err_miss_lbr(err);
        return false;
    }
    token t = stok_pop(st);
    while (t.type != TOK_LBR && !stok_is_empty(st)) {
        qtok_push(postfix, t);
        t = stok_pop(st);
    }
    if (t.type == TOK_LBR) {
        if (!stok_is_empty(st) && stok_peek(st).type == TOK_FUNC) {
            t = stok_pop(st);
            qtok_push(postfix, t);
        }
        return true;
    }
    qtok_push(postfix, t);
    err_miss_lbr(err);
    return false;
}

static bool pop_to_end(stack_token *st, queue_token *postfix, error *err) {
    bool tmp = pop_to_lbr(st, postfix, err);
    if (tmp) err_miss_rbr(err);
    else {
        err->is_error = false;
        strcpy(err->error_text, "");
    }
    return !tmp;
}

static void push_op(token t_op, stack_token *st, queue_token *postfix) {
    int pr = get_priority(t_op.op);
    bool is_l = is_left_op(t_op.op);
    while (!stok_is_empty(st)) {
        token t = stok_peek(st);
        if (t.type == TOK_LBR ||
            (is_l && get_priority(t.op) > pr) ||
            (!is_l && get_priority(t.op) >= pr)) break;
        stok_pop(st);
        qtok_push(postfix, t);
    }
    stok_push(st, t_op);
}

static bool push_arg(stack_token *st, queue_token *postfix, error *err) {
    while (!stok_is_empty(st)) {
        token t = stok_peek(st);
        if (t.type == TOK_LBR) return true;
        else if (t.type != TOK_OP) break;
        stok_pop(st);
        qtok_push(postfix, t);
    }
    err->is_error = true;
    strcpy(err->error_text, "opening bracket or arguments separator is missing");
    return false;
}


bool sorting_station(queue_token *infix, queue_token *postfix, error *err) {
    stack_token st;
    stok_init(&st);

    token_type prev = TOK_NULL;
    while (!qtok_is_empty(infix)) {
        token t = qtok_pop(infix);
        if (!check_token(prev, t)) {
            err->is_error = true;
            strcpy(err->error_text, "wrong expression");
            break;
        }
        if (t.type == TOK_VAL || t.type == TOK_VAR)
            qtok_push(postfix, t);
        else if (t.type == TOK_LBR || t.type == TOK_FUNC)
            stok_push(&st, t);
        else if (t.type == TOK_RBR) {
            if (!pop_to_lbr(&st, postfix, err)) break;
        }
        else if (t.type == TOK_OP)
            push_op(t, &st, postfix);
        else if (t.type == TOK_SEP) {
            if (!push_arg(&st, postfix, err)) break;
        }
        prev = t.type;
    }
    if (err->is_error) {
        stok_destroy(&st);
        return false;
    }
    pop_to_end(&st, postfix, err);
    stok_destroy(&st);
    if (err->is_error) return false;
    return true;
}