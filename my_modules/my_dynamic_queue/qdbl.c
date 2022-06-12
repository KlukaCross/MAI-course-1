#include "qdbl.h"
#define K_SIZE 2

static void shift_front(queue_dbl *q) {
    for (size_t i = q->first; i < q->size; i++) {
        q->buf[q->size*(K_SIZE-1)+i] = q->buf[i];
    }
    q->first += q->size;
}

static void shift_back(queue_dbl *q, size_t shift, size_t count) {
    for (size_t i = q->first; i < q->first + count; i++) {
        q->buf[i-shift] = q->buf[i];
    }
    q->first = q->first - shift;
}

static void shrink_buffer(queue_dbl *q) {
    size_t new_pool_size = q->pool_size / K_SIZE;
    if ((q->first+q->size) % q->pool_size > new_pool_size) {
        shift_back(q, q->first, q->size);
    }
    else if (q->first > new_pool_size) {
        shift_back(q, q->pool_size-new_pool_size, q->pool_size-q->first);
    }
    q->pool_size = new_pool_size;
    q->buf = realloc(q->buf, q->pool_size*sizeof(double));
}

static bool grow_buffer(queue_dbl *q) {
    size_t new_size = q->pool_size * K_SIZE;
    if (q->pool_size == 0) new_size = 2 * K_SIZE;
    double *new_buf = realloc(q->buf, new_size * sizeof(double));
    if (new_buf == NULL) return false;
    q->buf = new_buf;
    q->pool_size = new_size;
    if (q->pool_size != 0 && (q->first + q->size) % q->pool_size <= q->first) shift_front(q);
    return true;
}

void qdbl_init(queue_dbl *q) {
    q->size = 0;
    q->pool_size = 0;
    q->buf = NULL;
    q->first = 0;
}

void qdbl_destroy(queue_dbl *q) {
    q->size = 0;
    q->pool_size = 0;
    free(q->buf);
    q->buf = NULL;
    q->first = 0;
}

bool qdbl_push(queue_dbl *q, double el) {
    if (q->size >= q->pool_size) {
        if (!grow_buffer(q)) return false;
    }
    q->buf[(q->first + q->size) % q->pool_size] = el;
    q->size++;
    return true;
}

double qdbl_pop(queue_dbl *q) {
    double res = q->buf[q->first];
    q->first = (q->first+1) % q->pool_size;
    q->size--;
    if (q->size * 4 <= q->pool_size) {
        shrink_buffer(q);
    }
    return res;
}
double qdbl_peek(queue_dbl *q) {
    return q->buf[q->first];
}

bool qdbl_is_empty(queue_dbl *q) {
    return q->size == 0;
}

