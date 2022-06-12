#include "qdbl.h"

void qdbl_init(queue_dbl *q) {
    q->size = 0;
    q->first = 0;
}

void qdbl_destroy(queue_dbl *q) {
    q->size = 0;
    q->first = 0;
}

bool qdbl_push(queue_dbl *q, double el) {
    if (q->size >= POOL_SIZE) return false;
    q->buf[(q->first + q->size) % POOL_SIZE] = el;
    q->size++;
    return true;
}

double qdbl_peek(queue_dbl *q) {
    return q->buf[q->first];
}

double qdbl_pop(queue_dbl *q) {
    double el = q->buf[q->first];
    q->first = (q->first+1) % POOL_SIZE;
    q->size--;
    return el;
}

bool qdbl_is_empty(queue_dbl *q) {
    return q->size == 0;
}
