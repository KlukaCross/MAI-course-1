#include "list.h"
#define K_SIZE 2
#define INITIAL_SIZE 8

static int get_next(list_iter *it) {
    return it->lst->buf[it->cur].pn ^ it->prev;
}

static int get_prev_before(list_iter *it) {
    return it->cur ^ it->lst->buf[it->prev].pn;
}

static int pop_empty(barrier_list *lst) {
    int res = lst->first_empty;
    lst->first_empty = lst->buf[res].pn ^ lst->last_add;
    lst->last_add = res;
    return res;
}

static bool grow_buffer(barrier_list *l) {
    int new_size = l->pool_size * K_SIZE;
    listel *new_buf = realloc(l->buf, (new_size+1) * sizeof(listel));
    if (new_buf == NULL) return false;
    l->buf = new_buf;
    int old_barrier = l->barrier;
    l->barrier = new_size;
    for (int i = l->pool_size+1; i < new_size; ++i) {
        l->buf[i].pn = (i-1)^(i+1);
    }
    l->buf[l->barrier].pn = l->buf[old_barrier].pn;
    l->buf[old_barrier].pn = l->last_add ^ (old_barrier + 1);
    l->first_empty = old_barrier;
    int last = l->buf[l->barrier].pn ^ l->first;
    l->buf[last].pn = l->buf[last].pn ^ old_barrier ^ l->barrier;
    l->buf[l->first].pn = l->buf[l->first].pn ^ old_barrier ^ l->barrier;
    l->pool_size = new_size;
    return true;
}

bool list_init(barrier_list *l) {
    l->buf = malloc((INITIAL_SIZE+1) * sizeof(listel));
    if (l->buf == NULL) return false;
    l->pool_size = INITIAL_SIZE;
    l->barrier = INITIAL_SIZE;
    l->first = l->barrier;
    l->size = 0;
    // связываем пустые элементы:
    for (int i = 1; i < l->pool_size; ++i) {
        l->buf[i].pn = (i-1)^(i+1);
    }
    l->buf[0].pn = 1^l->barrier;
    l->buf[l->barrier].pn = 0;
    l->first_empty = 0;
    l->last_add = l->barrier;
    return true;
}
void list_destroy(barrier_list *l) {
    list_iter it = list_iter_begin(l);
    while (!list_iter_equal(it, list_iter_end(l))) {
        list_iter_remove(&it);
    }
}
int list_get_size(barrier_list *l) {
    return l->size;
}

list_iter list_iter_begin(barrier_list *l) {
    list_iter it;
    it.lst = l;
    it.prev = l->barrier;
    it.cur = l->first;
    return it;
}

list_iter list_iter_end(barrier_list *l) {
    list_iter it;
    it.lst = l;
    it.cur = l->barrier;
    it.prev = l->buf[l->barrier].pn ^ l->first;
    return it;
}

bool list_iter_equal(list_iter it1, list_iter it2) {
    return it1.prev == it2.prev && it1.cur == it2.cur && it1.lst == it2.lst;
}

void list_iter_move_next(list_iter *it) {
    int next = get_next(it);
    it->prev = it->cur;
    it->cur = next;
}

void list_iter_move_back(list_iter *it) {
    int prev_before = get_prev_before(it);
    it->cur = it->prev;
    it->prev = prev_before;
}

int list_iter_get(list_iter *it) {
    return it->lst->buf[it->cur].val;
}

void list_iter_set(list_iter *it, int val) {
    it->lst->buf[it->cur].val = val;
}

bool list_iter_insert_before(list_iter *it, int val) {
    if (it->lst->size >= it->lst->pool_size) {
        int old_barrier = it->lst->barrier;
        if (!grow_buffer(it->lst)) return false;
        if (it->cur == old_barrier) it->cur = it->lst->barrier;
        if (it->prev == old_barrier) it->prev = it->lst->barrier;
    }
    int new_id = pop_empty(it->lst);
    listel* new_el = &it->lst->buf[new_id];
    new_el->pn = it->cur ^ it->prev;
    new_el->val = val;
    int next = get_next(it);
    if (list_get_size(it->lst) > 0) {
        it->lst->buf[it->prev].pn = get_prev_before(it) ^ new_id;
        it->lst->buf[it->cur].pn = new_id ^ next;
    }
    it->prev = new_id;
    it->lst->size++;
    if (it->cur == it->lst->first) {
        it->lst->first = new_id;
    }
    return true;
}

void list_iter_remove(list_iter *it) {
    int next = get_next(it);
    if (list_get_size(it->lst) > 1) {
        it->lst->buf[it->prev].pn = get_prev_before(it) ^ next;
        it->lst->buf[next].pn = it->lst->buf[next].pn ^ it->cur ^ it->prev;
    }
    if (it->lst->first == it->cur) {
        it->lst->first = next;
    }
    if (it->lst->first_empty != it->lst->barrier)
        it->lst->buf[it->lst->first_empty].pn =
                it->lst->buf[it->lst->first_empty].pn ^
                it->lst->last_add ^ it->cur;
    it->lst->buf[it->cur].pn = it->lst->last_add ^ it->lst->first_empty;
    it->lst->first_empty = it->cur;
    it->cur = next;
    it->lst->size--;
}

list_iter list_iter_find(barrier_list *l, int val) {
    list_iter iter = list_iter_begin(l);
    for (;
    !list_iter_equal(iter, list_iter_end(l));
    list_iter_move_next(&iter)
    ) {
        if (list_iter_get(&iter) == val) break;
    }
    return iter;
}