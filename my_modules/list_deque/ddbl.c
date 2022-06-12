#include "ddbl.h"

void ddbl_init(deque_dbl *q) {
    q->first = NULL;
    q->last = NULL;
}

bool ddbl_is_empty(deque_dbl *q) {
    return q->first == NULL;
}

double ddbl_peek_front(deque_dbl *q) {
    return q->first->val;
}

double ddbl_peek_back(deque_dbl *q) {
    return q->last->val;
}

bool ddbl_push_back(deque_dbl *d, double val) {
    deque_dbl_elem *new_el = malloc(sizeof(deque_dbl_elem));
    if (new_el == NULL) return false;
    new_el->val = val;
    new_el->next = NULL;
    new_el->prev = d->last;
    if (d->last != NULL) {
        d->last->next = new_el;
    } else {
        d->first = new_el;
    }
    d->last = new_el;
    return true;
}

bool ddbl_push_front(deque_dbl *q, double val) {
    deque_dbl_elem *new_el = malloc(sizeof(deque_dbl_elem));
    if (new_el == NULL) return false;
    new_el->val = val;
    new_el->prev = NULL;
    new_el->next = q->first;
    if (q->first != NULL) {
        q->first->prev = new_el;
    } else {
        q->last = new_el;
    }
    q->first = new_el;
    return true;
}

double ddbl_pop_front(deque_dbl *d) {
    deque_dbl_elem *tmp = d->first;
    d->first = d->first->next;
    if (d->last == tmp) d->last = NULL;
    if (d->first != NULL) d->first->prev = NULL;
    double res = tmp->val;
    free(tmp);
    return res;
}

double ddbl_pop_back(deque_dbl *d) {
    deque_dbl_elem *tmp = d->last;
    d->last = d->last->prev;
    if (d->first == tmp) d->first = NULL;
    if (d->last != NULL) d->last->next = NULL;
    double res = tmp->val;
    free(tmp);
    return res;
}

void ddbl_destroy(deque_dbl *q) {
    while (!ddbl_is_empty(q)) {
        ddbl_pop_back(q);
    }
}