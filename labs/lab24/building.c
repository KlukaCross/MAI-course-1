#include "building.h"

static void exp_err(error *err) {
    err->is_error = true;
    strcpy(err->error_text, "wrong expression");
}

void build_tree(queue_token *postfix, tree_token *tree, error *err) {
    stack_tree_token st;
    stt_init(&st);
    while (!qtok_is_empty(postfix)) {
        token t = qtok_pop(postfix);
        if (t.type == TOK_VAL || t.type == TOK_VAR) {
            tree_token tn = ttok_build(NULL, NULL, t);
            stt_push(&st, tn);
            continue;
        }

        if (stt_is_empty(&st)) {
            exp_err(err);
            break;
        }
        tree_token left = stt_pop(&st);
        if ((t.type == TOK_OP && is_unary_op(t.op)) ||
            (t.type == TOK_FUNC && is_unary_func(t.func))) {
            stt_push(&st, ttok_build(NULL, left, t));
            continue;
        }

        if (stt_is_empty(&st)) {
            exp_err(err);
            break;
        }
        tree_token right = stt_pop(&st);
        stt_push(&st, ttok_build(left, right, t));
    }
    if (err->is_error) {
        stt_destroy(&st);
        return;
    }
    tree_token res = stt_pop(&st);
    if (!stt_is_empty(&st)) exp_err(err);
    stt_destroy(&st);
    *tree = res;
}

void build_union_tree(tree_token tree1, tree_token tree2, tree_token *union_tree, token union_func, int polynom_degree, int k) {
    tree_token r1 = ttok_get_right(tree1);
    tree_token r2 = ttok_get_right(tree2);
    tree_token u_l = ttok_create_empty();
    tree_token u_r = ttok_create_empty();
    if (k < polynom_degree) {
        build_union_tree(r1, r2, &u_r, union_func, polynom_degree, k + 1);
    } else {
        ttok_copy(tree1, &u_r);
        ttok_copy(tree2, &u_l);
        *union_tree = ttok_build(u_l, u_r, union_func);
        return;
    }

    tree_token l1 = ttok_get_left(tree1);
    tree_token l2 = ttok_get_left(tree2);
    tree_token u_l_r = ttok_create_empty();
    tree_token u_l_r_l = ttok_create_empty();
    tree_token u_l_r_r = ttok_create_empty();
    tree_token u_l_l = ttok_create_empty();

    ttok_copy(ttok_get_right(l1), &u_l_r_r);
    ttok_copy(ttok_get_right(l2), &u_l_r_l);
    u_l_r = ttok_build(u_l_r_l, u_l_r_r, union_func);

    ttok_copy(ttok_get_left(l1), &u_l_l);

    u_l = ttok_build(u_l_l, u_l_r, ttok_get_root_val(l1));
    *union_tree = ttok_build(u_l, u_r, ttok_get_root_val(tree1));
}

void build_postfix(tree_token tree, queue_token *postfix) {
    if (ttok_is_empty(tree)) return;
    tree_token right = ttok_get_right(tree);
    tree_token left = ttok_get_left(tree);
    build_postfix(right, postfix);
    build_postfix(left, postfix);
    qtok_push(postfix, ttok_get_root_val(tree));
}

void build_infix(tree_token tree, queue_token *buf, int *min_pr) {
    if (ttok_is_empty(tree)) return;
    token t = ttok_get_root_val(tree);
    if (t.type == TOK_VAR || t.type == TOK_VAL) {
        qtok_push(buf, t);
        return;
    }
    tree_token right = ttok_get_right(tree);
    tree_token left = ttok_get_left(tree);
    queue_token buf_left;
    qtok_init(&buf_left);
    queue_token buf_right;
    qtok_init(&buf_right);
    token brl;
    brl.type = TOK_LBR;
    token brr;
    brr.type = TOK_RBR;
    if (t.type == TOK_OP) {
        int pr_op = get_priority(t.op);
        if (min_pr != NULL && pr_op > (*min_pr))
            (*min_pr) = pr_op;
        int min_pr_left = pr_op;
        int min_pr_right = pr_op;
        build_infix(left, &buf_left, &min_pr_left);
        build_infix(right, &buf_right, &min_pr_right);
        if (is_unary_op(t.op)) {
            qtok_push(buf, t);
            if (pr_op < min_pr_right) qtok_push(buf, brl);
            qtok_move(&buf_right, buf);
            if (pr_op < min_pr_right) qtok_push(buf, brr);
        } else {
            if (pr_op < min_pr_right) qtok_push(buf, brl);
            qtok_move(&buf_right, buf);
            if (pr_op < min_pr_right) qtok_push(buf, brr);
            qtok_push(buf, t);
            if (pr_op < min_pr_left) qtok_push(buf, brl);
            qtok_move(&buf_left, buf);
            if (pr_op < min_pr_left) qtok_push(buf, brr);
        }
    } else if (t.type == TOK_FUNC) {
        build_infix(left, &buf_left, NULL);
        build_infix(right, &buf_right, NULL);
        qtok_push(buf, t);
        qtok_push(buf, brl);
        qtok_move(&buf_right, buf);
        if (is_binary_func(t.func)) {
            token sep;
            sep.type = TOK_SEP;
            qtok_push(buf, sep);
            qtok_move(&buf_left, buf);
        }
        qtok_push(buf, brr);
    }
    qtok_destroy(&buf_right);
    qtok_destroy(&buf_left);
}
