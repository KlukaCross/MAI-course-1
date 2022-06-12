#include "token_queue.h"
#include "token_tree.h"
#include "user_interface.h"
#include "sorting_station.h"
#include "error_struct.h"
#include "building.h"

static bool make_tree(queue_token* infix, queue_token* postfix, tree_token* tree, int *polynom_degree, error* err) {
    queue_token infix_copy;
    queue_token postfix_copy;
    qtok_init(&infix_copy);
    qtok_init(&postfix_copy);
    *polynom_degree = read_coefficients(infix, err);
    qtok_copy(infix, &infix_copy);
    if (err->is_error || qtok_is_empty(infix)) return false;
    sorting_station(&infix_copy, postfix, err);
    qtok_copy(postfix, &postfix_copy);
    if (err->is_error) return false;
    if (!qtok_is_empty(&postfix_copy))
        build_tree(&postfix_copy, tree, err);
    if (err->is_error) return false;
    qtok_destroy(&infix_copy);
    qtok_destroy(&postfix_copy);
    return true;
}

static void print_polinom_infix(queue_token infix, char *func_name) {
    printf("\n---------------------------------------------------------\n");
    printf("Polynomial %s in text: \n", func_name);
    print_expression(infix);
}

static void print_polinom_tree(tree_token tree, char *func_name) {
    printf("Polynomial %s in tree: \n", func_name);
    print_tree(tree, 0);
}


int main() {
    queue_token f_infix;
    qtok_init(&f_infix);
    queue_token f_postfix;
    qtok_init(&f_postfix);
    tree_token f_tree = ttok_create_empty();
    int f_degree = 0;

    queue_token g_infix;
    qtok_init(&g_infix);
    queue_token g_postfix;
    qtok_init(&g_postfix);
    tree_token g_tree = ttok_create_empty();
    int g_degree = 0;

    queue_token h1_infix;
    qtok_init(&h1_infix);
    token h1_func;
    h1_func.type = TOK_FUNC;
    strcpy(h1_func.func, "max");
    tree_token h1_tree = ttok_create_empty();

    queue_token h2_infix;
    qtok_init(&h2_infix);
    token h2_func;
    h2_func.type = TOK_FUNC;
    strcpy(h2_func.func, "min");
    tree_token h2_tree = ttok_create_empty();

    queue_token h3_infix;
    qtok_init(&h3_infix);
    token h3_func;
    h3_func.type = TOK_OP;
    h3_func.op = '*';
    tree_token h3_tree = ttok_create_empty();

    queue_token h4_infix;
    qtok_init(&h4_infix);
    token h4_func;
    h4_func.type = TOK_OP;
    h4_func.op = '/';
    tree_token h4_tree = ttok_create_empty();

    error err;
    err.is_error = false;
    bool res_make = true;
    
    printf("The program reads coefficients for polynomials \n"
           "f(x) = a1 + a2*x + a3*x^2 + ... + an*x^(n-1) \n"
           "g(x) = b1 + b2*x + b3*x^2 + ... + bn*x^(n-1) \n"
           "and then builds polynomials \n"
           "h1(x) = max(a1, b1) + max(a2, b2)*x + ... + max(an, bn)*x^(n-1)\n"
           "h2(x) = min(a1, b1) + min(a2, b2)*x + ... + min(an, bn)*x^(n-1)\n"
           "h3(x) = a1*b1 + a2*b2*x + ... + an*bn*x^(n-1)\n"
           "h4(x) = a1/b1 + a2/b2*x + ... + an/bn*x^(n-1)\n"
           "from f and g, if they are the same degree.\n"
           "Supported functions: sin(x), cos(x), min(x,y), max(x,y).\n"
           "Attention, the coefficients must be separated by a space!\n"
           "---------------------------------------------------------\n");

    printf("Input the coefficients for the polynomial f:\n");
    res_make = make_tree(&f_infix, &f_postfix, &f_tree, &f_degree,&err);
    if (!res_make) {
        if (err.is_error) {
            printf("%s\n", err.error_text);
            return 1;
        }
        return 0;
    }

    printf("Input the coefficients for the polynomial g:\n");
    res_make = make_tree(&g_infix, &g_postfix, &g_tree, &g_degree, &err);
    if (!res_make) {
        if (err.is_error) {
            printf("%s\n", err.error_text);
            return 1;
        }
        return 0;
    }

    print_polinom_infix(f_infix, "f");
    print_polinom_infix(g_infix, "g");

    if (f_degree != g_degree) {
        printf("The polynomials f and g have different degrees - "
               "the construction of polynomials h1, h2, h3, h4 is impossible.");
        return 1;
    }

    build_union_tree(f_tree, g_tree, &h1_tree, h1_func, f_degree, 0);
    build_union_tree(f_tree, g_tree, &h2_tree, h2_func, f_degree, 0);
    build_union_tree(f_tree, g_tree, &h3_tree, h3_func, f_degree, 0);
    build_union_tree(f_tree, g_tree, &h4_tree, h4_func, f_degree, 0);

    build_infix(h1_tree, &h1_infix, NULL);
    build_infix(h2_tree, &h2_infix, NULL);
    build_infix(h3_tree, &h3_infix, NULL);
    build_infix(h4_tree, &h4_infix, NULL);

    print_polinom_infix(h1_infix, "h1");
    print_polinom_tree(h1_tree, "h1");
    print_polinom_infix(h2_infix, "h2");
    print_polinom_tree(h2_tree, "h2");
    print_polinom_infix(h3_infix, "h3");
    print_polinom_tree(h3_tree, "h3");
    print_polinom_infix(h4_infix, "h4");
    print_polinom_tree(h4_tree, "h4");

    return 0;
}
