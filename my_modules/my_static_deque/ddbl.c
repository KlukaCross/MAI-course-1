#include "ddbl.h"

void ddbl_init(deque_dbl *d) {
    d->size = 0;
    d->first = 0;
}

void ddbl_destroy(deque_dbl *d) {
    d->size = 0;
    d->first = 0;
}

bool ddbl_push_back(deque_dbl *d, double el) {
    if (d->size >= POOL_SIZE) return false;
    d->buf[(d->first + d->size) % POOL_SIZE] = el;
    d->size++;
    return true;
}

double ddbl_peek_front(deque_dbl *d) {
    return d->buf[d->first];
}

double ddbl_pop_front(deque_dbl *d) {
    double el = ddbl_peek_front(d);
    d->first = (d->first+1) % POOL_SIZE;
    d->size--;
    return el;
}

bool ddbl_push_front(deque_dbl *d, double el) {
    if (d->size >= POOL_SIZE) return false;
    d->first = (d->first+POOL_SIZE-1) % POOL_SIZE;
    d->buf[d->first] = el;
    d->size++;
    return true;
}

double ddbl_peek_back(deque_dbl *d) {
    return d->buf[(d->first + d->size) % POOL_SIZE];
}

double ddbl_pop_back(deque_dbl *d) {
    double el = ddbl_peek_back(d);
    d->size--;
    return el;
}

bool ddbl_is_empty(deque_dbl *d) {
    return d->size == 0;
}
