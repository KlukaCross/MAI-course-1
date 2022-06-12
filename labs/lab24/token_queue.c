#include "token_queue.h"
#define K_SIZE 2

static void shift_front(queue_token *q) {
    for (size_t i = q->first; i < q->size; i++) {
        q->buf[q->size*(K_SIZE-1)+i] = q->buf[i];
    }
    q->first += q->size;
}

static void shift_back(queue_token *q, size_t shift, size_t count) {
    for (size_t i = q->first; i < q->first + count; i++) {
        q->buf[i-shift] = q->buf[i];
    }
    q->first = q->first - shift;
}

static void shrink_buffer(queue_token *q) {
    size_t new_pool_size = q->pool_size / K_SIZE;
    if ((q->first+q->size) % q->pool_size > new_pool_size) {
        shift_back(q, q->first, q->size);
    }
    else if (q->first > new_pool_size) {
        shift_back(q, q->pool_size-new_pool_size, q->pool_size-q->first);
    }
    q->pool_size = new_pool_size;
    q->buf = realloc(q->buf, q->pool_size*sizeof(token));
}

static bool grow_buffer(queue_token *q) {
    size_t new_size = q->pool_size * K_SIZE;
    if (q->pool_size == 0) new_size = 2 * K_SIZE;
    token *new_buf = realloc(q->buf, new_size * sizeof(token));
    if (new_buf == NULL) return false;
    q->buf = new_buf;
    q->pool_size = new_size;
    if (q->pool_size != 0 && (q->first + q->size) % q->pool_size <= q->first) shift_front(q);
    return true;
}

void qtok_init(queue_token *q) {
    q->size = 0;
    q->pool_size = 0;
    q->buf = NULL;
    q->first = 0;
}

void qtok_destroy(queue_token *q) {
    q->size = 0;
    q->pool_size = 0;
    free(q->buf);
    q->buf = NULL;
    q->first = 0;
}

bool qtok_push(queue_token *q, token el) {
    if (q->size >= q->pool_size) {
        if (!grow_buffer(q)) return false;
    }
    q->buf[(q->first + q->size) % q->pool_size] = el;
    q->size++;
    return true;
}

token qtok_pop(queue_token *q) {
    token res = q->buf[q->first];
    q->first = (q->first+1) % q->pool_size;
    q->size--;
    if (q->size * 4 <= q->pool_size) {
        shrink_buffer(q);
    }
    return res;
}
token qtok_peek(queue_token *q) {
    return q->buf[q->first];
}

bool qtok_is_empty(queue_token *q) {
    return q->size == 0;
}

int qtok_get_size(queue_token *q) {
    return q->size;
}

void qtok_copy(queue_token *from, queue_token *to) {
    queue_token tmp;
    qtok_init(&tmp);
    while (!qtok_is_empty(from)) {
        token t_orig = qtok_pop(from);
        qtok_push(to, t_orig);
        qtok_push(&tmp, t_orig);
    }
    free(from->buf);
    *from = tmp;
}

void qtok_move(queue_token *from, queue_token *to) {
    while (!qtok_is_empty(from))
        qtok_push(to, qtok_pop(from));
}