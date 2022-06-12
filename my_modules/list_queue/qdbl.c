#include "qdbl.h"

void qdbl_init(queue_dbl *q) {
    q->first = NULL;
    q->last = NULL;
}

bool qdbl_is_empty(queue_dbl *q) {
    return q->first == NULL;
}

double qdbl_peek(queue_dbl *q) {
    return q->first->val;
}

bool qdbl_push(queue_dbl *q, double val) {
    queue_dbl_elem *new_el = malloc(sizeof(queue_dbl_elem));
    if (new_el == NULL) return false;
    new_el->val = val;
    new_el->next = NULL;
    if (q->last != NULL) {
        q->last->next = new_el;
    } else {
        q->first = new_el;
    }
    q->last = new_el;
    return true;
}

double qdbl_pop(queue_dbl *q) {
    queue_dbl_elem *tmp = q->first;
    q->first = q->first->next;
    if (q->last == tmp) q->last = NULL;
    double res = tmp->val;
    free(tmp);
    return res;
}

void qdbl_destroy(queue_dbl *q) {
    while (!qdbl_is_empty(q)) {
        qdbl_pop(q);
    }
}