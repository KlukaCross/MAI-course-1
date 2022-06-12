#include "user_interface.h"

#define MAX_LEN_BUF 15

typedef enum {
    STATE_SCAN,
    STATE_SCAN_ADD,
    STATE_SCAN_DEL,
    STATE_SCAN_DEL_POS,
    STATE_SCAN_POP,
    STATE_MISS
} state;

static bool is_sep(char ch) {
    return (('\t' <= ch && ch <= '\r') || ch == ' ');
}

static void break_str(char *buf, state* st, svector_int* vec_buf,
                      int* buf_int, int* buf_sign, bool *scan_digit) {
    buf[0] = '\0';
    *st = STATE_SCAN;
    while (!svint_is_empty(vec_buf))
        svint_pop_back(vec_buf);
    *buf_int = 0;
    *buf_sign = 1;
    *scan_digit = false;
}

static void conc_str(char *buf, char ch) {
    int l = strlen(buf);
    if (l < MAX_LEN_BUF) {
        buf[l + 1] = '\0';
        buf[l] = ch;
    }
}

static void conc_int(int *buf, char ch) {
    *buf = *buf * 10 + (ch - '0');
}

static bool is_digit(char ch) {
    return '0' <= ch && ch <= '9';
}

static void quick_sort(int ql, int qr, svector_int* v) {
    int l = ql, r = qr;
    int base = svint_get(v, (l+r)/2);
    while (l <= r) {
        while (svint_get(v, l) < base)
            l++;
        while (svint_get(v, r) > base)
            r--;
        if (l <= r) {
            int tmp = svint_get(v, l);
            svint_set(v, l++, svint_get(v, r));
            svint_set(v, r--, tmp);
        }
    }
    if (ql < r)
        quick_sort(ql, r, v);
    if (qr > l)
        quick_sort(l, qr, v);
}

void print_list(barrier_list *lst) {
    if (list_get_size(lst) == 0) {
        printf("list is empty\n");
        return;
    }
    list_iter it = list_iter_begin(lst);
    while(!list_iter_equal(it, list_iter_end(lst))) {
        printf("%d ", list_iter_get(&it));
        list_iter_move_next(&it);
    }
    printf("\n");
}

void print_help() {
    printf("h, help - output help\n"
           "add POSITION VALUE [VALUE2]... - add VALUE(s) to POSITION "
           "(position start from 0)"
           "(values must be integers)\n"
           "show - print list\n"
           "del VALUE [VALUE2]... - delete VALUE(s) from list "
           "(if there are several elements having the same value, "
           "the first one will be deleted)\n"
           "del_pos POSITION [POSITION2]... - delete elements on POSITION(s)\n"
           "pop K - delete last K elements\n"
           "exit - exit program\n");
}

void add(barrier_list *l, svector_int *buf) {
    if (svint_get_size(buf) < 2) {
        printf("wrong number of arguments\n");
        return;
    }
    int pos = svint_pop_front(buf);
    if (pos > list_get_size(l) || pos < 0) {
        printf("wrong argument POSITION\n");
        return;
    }
    list_iter iter = list_iter_begin(l);
    for (int i = 0; i < pos; i++) {
        list_iter_move_next(&iter);
    }
    for (int i = 0; i < svint_get_size(buf); ++i) {
        list_iter_insert_before(&iter, svint_get(buf, i));
    }
}

void del(barrier_list *l, svector_int* buf) {
    if (list_get_size(l) == 0) {
        printf("list is empty\n");
        return;
    }
    svector_int buf_not;
    svint_init(&buf_not);
    list_iter iter;
    for (int i = 0; i < svint_get_size(buf); ++i) {
        iter = list_iter_find(l, svint_get(buf, i));
        if (list_iter_equal(iter, list_iter_end(l)))
            svint_push_back(&buf_not, svint_get(buf, i));
        else
            list_iter_remove(&iter);
    }
    if (svint_get_size(&buf_not) != 0) {
        printf("next elements not in the list: ");
        int buf_not_size = svint_get_size(&buf_not);
        for (int i = 0; i < buf_not_size; ++i) {
            printf("%d ", svint_pop_front(&buf_not));
        }
        printf("\n");
    }
    svint_destroy(&buf_not);
}

void del_pos(barrier_list *l, svector_int* buf) {
    if (list_get_size(l) == 0) {
        printf("list is empty\n");
        return;
    }
    svector_int buf_not;
    svint_init(&buf_not);
    list_iter iter = list_iter_begin(l);
    quick_sort(0, svint_get_size(buf)-1, buf);
    int shift = 0;
    int cur_pos = 0;
    for (int i = 0; i < svint_get_size(buf); ++i) {
        int pos = svint_get(buf, i);
        if (pos < 0 || pos-shift >= list_get_size(l))
            svint_push_back(&buf_not, pos);
        else {
            int to = pos-cur_pos-shift;
            for (int k=0; k < to; k++) {
                list_iter_move_next(&iter);
                cur_pos++;
            }
            list_iter_remove(&iter);
            shift++;
        }
    }
    if (svint_get_size(&buf_not) != 0) {
        printf("next positions are incorrect: ");
        int buf_not_size = svint_get_size(&buf_not);
        for (int i = 0; i < buf_not_size; ++i) {
            printf("%d ", svint_pop_front(&buf_not));
        }
        printf("\n");
    }
    svint_destroy(&buf_not);
}

void print_size(barrier_list *l) {
    printf("%d\n", list_get_size(l));
}

void pop(barrier_list *l, int k) {
    if (list_get_size(l) < k) {
        printf("list size less than %d\n", k);
        return;
    }
    list_iter iter = list_iter_end(l);
    list_iter_move_back(&iter);
    for (int i = 0; i < k; ++i) {
        list_iter_remove(&iter);
        list_iter_move_back(&iter);
    }
}

void print_wrong_command() {
    printf("wrong command\n");
}

void loop(barrier_list *l) {
    char buf_str[MAX_LEN_BUF] = "";
    state st = STATE_SCAN;
    svector_int buf_vec;
    bool scan_digit = false;
    int buf_int = 0;
    int buf_sign = 1;
    svint_init(&buf_vec);
    int s;
    char ch;
    do {
        s = getchar();
        if (s != EOF) ch = s;
        else continue;

        if (st == STATE_MISS) {
            if (ch == '\n') {
                break_str(buf_str, &st, &buf_vec, &buf_int,
                          &buf_sign, &scan_digit);
                print_wrong_command();
            }
        }
        else if (ch == '\n') {
            if (scan_digit) svint_push_back(&buf_vec, buf_int * buf_sign);
            if (st == STATE_SCAN_ADD)
                add(l, &buf_vec);
            else if (st == STATE_SCAN_DEL)
                del(l, &buf_vec);
            else if (st == STATE_SCAN_DEL_POS)
                del_pos(l, &buf_vec);
            else if (st == STATE_SCAN_POP)
                pop(l, buf_int);
            else if (!strcmp(buf_str, "h") || !strcmp(buf_str, "help"))
                print_help();
            else if (!strcmp(buf_str, "show"))
                print_list(l);
            else if (!strcmp(buf_str, "size"))
                print_size(l);
            else if (!strcmp(buf_str, "exit"))
                return;
            else if (strlen(buf_str) != 0 || scan_digit)
                print_wrong_command();
            break_str(buf_str, &st, &buf_vec, &buf_int,
                      &buf_sign, &scan_digit);
        }
        else if (!is_sep(ch)) {
            if (is_digit(ch) || ch == '-') {
                if (strlen(buf_str) != 0)
                    st = STATE_MISS;
                else if (is_digit(ch))
                    conc_int(&buf_int, ch);
                else {
                    if (buf_sign == -1 || scan_digit) st = STATE_MISS;
                    else buf_sign = -1;
                }
                scan_digit = true;
            } else
                conc_str(buf_str, ch);
        }
        else if (!strcmp(buf_str, "add") ||
                !strcmp(buf_str, "del") ||
                !strcmp(buf_str, "pop") ||
                !strcmp(buf_str, "del_pos")) {
                if (!strcmp(buf_str, "add"))
                    st = STATE_SCAN_ADD;
                else if (!strcmp(buf_str, "del"))
                    st = STATE_SCAN_DEL;
                else if (!strcmp(buf_str, "del_pos"))
                    st = STATE_SCAN_DEL_POS;
                else
                    st = STATE_SCAN_POP;
                buf_str[0] = '\0';
        }
        else if (scan_digit) {
            svint_push_back(&buf_vec, buf_int * buf_sign);
            buf_int = 0;
            buf_sign = 1;
            scan_digit = false;
        }

    }
    while (s != EOF);
    svint_destroy(&buf_vec);
}