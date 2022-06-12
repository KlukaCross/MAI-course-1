#include "user_interface.h"

typedef enum {
    READ_RE,
    READ_PLUS,
    READ_IM_WITHOUT_I,
    READ_IM_WITH_I,
    READ_VALUE,
    READ_MISS
} state_read;

static bool is_sep(int ch) {
    return (('\t' <= ch && ch <= '\r') || ch == ' ');
}

static void reset_str(char *str) {
    str[0] = '\0';
}

static void conc_str(char *buf, char ch) {
    int l = strlen(buf);
    if (l < MAX_LEN_VALUE) {
        buf[l + 1] = '\0';
        buf[l] = ch;
    }
}

static void reset_item(item *it) {
    strcpy(it->val, "");
    __real__ it->key = 0;
    __imag__ it->key = 0;
}

static void print_one_item(item it) {
    char real[128];
    char imag[128];
    quadmath_snprintf(real, sizeof(real), "%Qf", crealq(it.key));
    quadmath_snprintf(imag, sizeof(imag), "%Qf", cimagq(it.key));
    printf("%s+%si %s\n", real, imag, it.val);
}

static void print_items_key(vector_item *v, int ind_key) {
    item item_key = vitem_get(v, ind_key);
    item new_item = item_key;
    while (!key_cmp(new_item.key, item_key.key)) {
        print_one_item(new_item);
        ind_key++;
        new_item = vitem_get(v, ind_key);
    }
}

static void loop_iter(state_read *st, char *str, int c, item *it) {
    if (*st == READ_MISS) return;
    else if (is_sep(c) && *st != READ_VALUE) {
        if (!strlen(str)) return;
        if (*st == READ_PLUS) {
            if (strcmp(str, "+")) {
                *st = READ_MISS;
                return;
            }
            *st = READ_IM_WITHOUT_I;
        } else if (*st == READ_RE) {
            __real__ (*it).key = strtold(str, NULL);
            *st = READ_PLUS;
        } else if (*st == READ_IM_WITH_I) {
            __imag__ (*it).key = strtold(str, NULL);
            *st = READ_VALUE;
        } else if (*st == READ_IM_WITHOUT_I) {
            *st = READ_MISS;
            return;
        }
        reset_str(str);
        return;
    } else if (c == 'i') {
        if (*st == READ_IM_WITHOUT_I) {
            *st = READ_IM_WITH_I;
            return;
        }
        else if (*st == READ_IM_WITH_I) {
            *st = READ_MISS;
            return;
        }
    } else if (c == '+' && (*st == READ_RE || *st == READ_PLUS)) {
        if (*st == READ_RE)
            __real__ (*it).key = strtold(str, NULL);
        *st = READ_IM_WITHOUT_I;
        reset_str(str);
        return;
    }
    conc_str(str, c);
}

void read_items(vector_item *v) {
    int c;
    char str[MAX_LEN_VALUE];
    state_read st = READ_RE;
    item it;
    reset_item(&it);
    reset_str(str);
    do {
        c = getchar();
        if (c == EOF) return;
        if (c == '\n') {
            if (!strcmp(str, "end") && st == READ_RE)
                return;
            if (!strlen(str) && st == READ_RE)
                continue;
            if (st != READ_VALUE) {
                printf("invalid entry\n");
            } else {
                strcpy(it.val, str);
                vitem_push_back(v, it);
            }
            st = READ_RE;
            reset_item(&it);
            reset_str(str);
            continue;
        }
        loop_iter(&st, str, c, &it);
    }
    while (true);
}

void read_keys(vector_item *v) {
    int c;
    char str[MAX_LEN_VALUE];
    state_read st = READ_RE;
    item it;
    reset_item(&it);
    reset_str(str);
    do {
        c = getchar();
        if (c == EOF) return;
        if (c == '\n') {
            if (!strcmp(str, "end") && st == READ_RE)
                return;
            if (!strlen(str) && st == READ_RE)
                continue;
            if (st == READ_IM_WITH_I) {
                __imag__ it.key = strtold(str, NULL);
                st = READ_VALUE;
            }
            if (st != READ_VALUE)
                printf("invalid key\n");
            else {
                int d = vitem_bin_search_key(v, it.key);
                if (d < 0)
                    printf("the key is not in the table\n");
                else
                    print_items_key(v, d);
            }
            st = READ_RE;
            reset_item(&it);
            reset_str(str);
            continue;
        }
        loop_iter(&st, str, c, &it);
    }
    while (true);
}

void print_items(vector_item *v) {
    for (int i = 0; i < vitem_get_size(v); i++) {
        print_one_item(vitem_get(v, i));
    }
}