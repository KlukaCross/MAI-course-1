#include "token_vector.h"

static const int K_SIZE = 2;

static bool grow_buffer(vector_token *v);
static void shift_front(vector_token *v);
static void shift_back(vector_token *v, size_t shift, size_t count);
static void shrink_buffer(vector_token *v);

void vtok_init(vector_token *v) {
    v->size = 0;
    v->pool_size = 0;
    v->buf = NULL;
    v->first = 0;
}

void vtok_destroy(vector_token *v) {
    v->size = 0;
    v->pool_size = 0;
    free(v->buf);
    v->buf = NULL;
    v->first = 0;
}

size_t vtok_get_size(vector_token *v) {
    return v->size;
}

bool vtok_set_size(vector_token *v, size_t new_size) {
    if (new_size < v->size) {
        v->size = new_size;
        if (v->size * 4 <= v->pool_size) {
            shrink_buffer(v);
        }
        if (v->size == 0)
            v->first = 0;
    }
    else if (new_size > v->size) {
        if (new_size > v->pool_size) {
            if (!grow_buffer(v)) return false;
        }
        token t;
        t.type = TOK_NULL;
        for (size_t i = v->size; i < new_size; i++) {
            v->buf[(v->first + i) % v->pool_size] = t;
        }
        v->size = new_size;
    }
    return true;
}

bool vtok_push_front(vector_token *v, token val) {
    if (!vtok_set_size(v, v->size+1)) return false;
    v->first = (v->first - v->pool_size-1) % v->pool_size;
    v->buf[v->first] = val;
    return true;
}

bool vtok_push_back(vector_token *v, token val) {
    if (!vtok_set_size(v, v->size+1)) return false;
    v->buf[(v->first + v->size-1) % v->pool_size] = val;
    return true;
}

token vtok_pop_front(vector_token *v) {
    token res = vtok_get_front(v);
    v->first = (v->first+1) % v->pool_size;
    vtok_set_size(v, v->size-1);
    return res;
}

token vtok_pop_back(vector_token *v) {
    token res = vtok_get_back(v);
    vtok_set_size(v, v->size-1);
    return res;
}

token vtok_get(vector_token *v, size_t i) {
    return v->buf[(v->first + i) % v->pool_size];
}
void vtok_set(vector_token *v, size_t i, token val) {
    v->buf[(v->first + i) % v->pool_size] = val;
}

token vtok_get_front(vector_token *v) {
    return v->buf[v->first];
}

token vtok_get_back(vector_token *v) {
    return v->buf[(v->first + v->size-1) % v->pool_size];
}

bool vtok_is_empty(vector_token *v) {
    return v->size == 0;
}

static bool grow_buffer(vector_token *v) {
    size_t new_size = v->pool_size * K_SIZE;
    if (v->pool_size == 0) new_size = 2 * K_SIZE;
    token *new_buf = realloc(v->buf, new_size * sizeof(token));
    if (new_buf == NULL) return false;
    v->buf = new_buf;
    v->pool_size = new_size;
    if (v->pool_size != 0 && (v->first + v->size) % v->pool_size <= v->first) shift_front(v);
    return true;
}

static void shift_front(vector_token *v) {
    for (size_t i = v->first; i < v->size; i++) {
        v->buf[v->size * (K_SIZE - 1) + i] = v->buf[i];
    }
    v->first = v->first + v->size;
}

static void shift_back(vector_token *v, size_t shift, size_t count) {
    for (size_t i = v->first; i < v->first + count; i++) {
        v->buf[i - shift] = v->buf[i];
    }
    v->first = v->first - shift;
}

static void shrink_buffer(vector_token *v) {
    size_t new_pool_size = v->pool_size / K_SIZE;
    if ((v->first + v->size) % v->pool_size > new_pool_size) {
        shift_back(v, v->first, v->size);
    }
    else if (v->first > new_pool_size) {
        shift_back(v, v->pool_size - new_pool_size, v->pool_size - v->first);
    }
    v->pool_size = new_pool_size;
    v->buf = realloc(v->buf, v->pool_size * sizeof(token));
}
