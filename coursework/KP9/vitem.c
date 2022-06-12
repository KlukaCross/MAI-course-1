#include "vitem.h"

static const int K_SIZE = 2;

static bool grow_buffer(vector_item *v);
static void shift_front(vector_item *v);
static void shift_back(vector_item *v, size_t shift, size_t count);
static void shrink_buffer(vector_item *v);

void vitem_init(vector_item *v) {
    v->size = 0;
    v->pool_size = 0;
    v->buf = NULL;
    v->first = 0;
}

void vitem_destroy(vector_item *v) {
    v->size = 0;
    v->pool_size = 0;
    free(v->buf);
    v->buf = NULL;
    v->first = 0;
}

size_t vitem_get_size(vector_item *v) {
    return v->size;
}

bool vitem_set_size(vector_item *v, size_t new_size) {
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
        for (size_t i = v->size; i < new_size; i++) {
            item it;
            __real__ it.key = 0;
            __imag__ it.key = 0;
            v->buf[(v->first + i) % v->pool_size] = it;
        }
        v->size = new_size;
    }
    return true;
}

bool vitem_push_front(vector_item *v, item val) {
    if (!vitem_set_size(v, v->size+1)) return false;
    v->first = (v->first - v->pool_size-1) % v->pool_size;
    v->buf[v->first] = val;
    return true;
}

bool vitem_push_back(vector_item *v, item val) {
    if (!vitem_set_size(v, v->size+1)) return false;
    v->buf[(v->first + v->size-1) % v->pool_size] = val;
    return true;
}

item vitem_pop_front(vector_item *v) {
    item res = vitem_get_front(v);
    v->first = (v->first+1) % v->pool_size;
    vitem_set_size(v, v->size-1);
    return res;
}

item vitem_pop_back(vector_item *v) {
    item res = vitem_get_back(v);
    vitem_set_size(v, v->size-1);
    return res;
}

item vitem_get(vector_item *v, size_t i) {
    return v->buf[(v->first + i) % v->pool_size];
}
void vitem_set(vector_item *v, size_t i, item val) {
    v->buf[(v->first + i) % v->pool_size] = val;
}

item vitem_get_front(vector_item *v) {
    return v->buf[v->first];
}

item vitem_get_back(vector_item *v) {
    return v->buf[(v->first + v->size-1) % v->pool_size];
}

bool vitem_is_empty(vector_item *v) {
    return v->size == 0;
}

void vitem_swap(vector_item *v, int i, int j) {
    item tmp = vitem_get(v, i);
    vitem_set(v, i, vitem_get(v, j));
    vitem_set(v, j, tmp);
}

static bool grow_buffer(vector_item *v) {
    size_t new_size = v->pool_size * K_SIZE;
    if (v->pool_size == 0) new_size = 2 * K_SIZE;
    item *new_buf = realloc(v->buf, new_size * sizeof(item));
    if (new_buf == NULL) return false;
    v->buf = new_buf;
    v->pool_size = new_size;
    if (v->pool_size != 0 && (v->first + v->size) % v->pool_size <= v->first) shift_front(v);
    return true;
}

static void shift_front(vector_item *v) {
    for (size_t i = v->first; i < v->size; i++) {
        v->buf[v->size * (K_SIZE - 1) + i] = v->buf[i];
    }
    v->first = v->first + v->size;
}

static void shift_back(vector_item *v, size_t shift, size_t count) {
    for (size_t i = v->first; i < v->first + count; i++) {
        v->buf[i - shift] = v->buf[i];
    }
    v->first = v->first - shift;
}

static void shrink_buffer(vector_item *v) {
    size_t new_pool_size = v->pool_size / K_SIZE;
    if ((v->first + v->size) % v->pool_size > new_pool_size) {
        shift_back(v, v->first, v->size);
    }
    else if (v->first > new_pool_size) {
        shift_back(v, v->pool_size - new_pool_size, v->pool_size - v->first);
    }
    v->pool_size = new_pool_size;
    v->buf = realloc(v->buf, v->pool_size * sizeof(item));
}

int vitem_bin_search_key(vector_item *v, __complex128 key) {
    int l = 0, r = vitem_get_size(v);
    while (l < r) {
        int m = (l + r) / 2;
        __complex128 k = vitem_get(v, m).key;
        int res_cmp = key_cmp(key, k);
        if (res_cmp == 0) {
            if (m == 0 || key_cmp(vitem_get(v, m - 1).key, key))
                return m;
            r = m;
        }
        else if (res_cmp > 0)
            l = m + 1;
        else
            r = m;
    }
    if (r != vitem_get_size(v) && !key_cmp(vitem_get(v, r).key, key))
        return r;
    return -1;
}
