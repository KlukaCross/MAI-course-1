#include "sort_hoar.h"

typedef struct {
    int l;
    int r;
} pair;

static int partition(vector_item *v, int l, int r, item pivot) {
    int i = l, j = r;
    while (i <= j) {
        while (key_cmp(vitem_get(v, i).key, pivot.key) < 0)
            i++;
        while (key_cmp(vitem_get(v, j).key, pivot.key) > 0)
            j--;
        if (i <= j) {
            vitem_swap(v, i, j);
            i++;
            j--;
        }
    }
    return i;
}

static item peek_pivot(vector_item *v, int l, int r) {
    return vitem_get(v, (l+r)/2);
}

void sort_hoar(vector_item *v) {
    pair stack[sizeof(size_t)*8];
    stack[0].l = 0;
    stack[0].r = vitem_get_size(v)-1;
    int stack_count = 1;
    while (stack_count > 0) {
        pair p = stack[stack_count-1];
        stack_count--;
        int l = p.l;
        int r = p.r;
        while (l < r) {
            item pivot = peek_pivot(v, l, r);
            int d = partition(v, l, r, pivot);
            if (r-l-d > d) {
                stack[stack_count].l = d;
                stack[stack_count].r = r;
                r = d-1;
            } else {
                stack[stack_count].l = l;
                stack[stack_count].r = d-1;
                l = d;
            }
            stack_count++;
        }
    }
}
