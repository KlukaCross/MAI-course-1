
#ifndef MY_STATIC_DEQUE_DDBL_H
#define MY_STATIC_DEQUE_DDBL_H
#define POOL_SIZE 64
#include <stdbool.h>
typedef struct {
    size_t size;
    size_t first;
    double buf[POOL_SIZE];
} deque_dbl;

void qdbl_init(deque_dbl *d);
void qdbl_destroy(deque_dbl *d);
bool qdbl_push_back(deque_dbl *d, double el);
double qdbl_pop_front(deque_dbl *d);
double qdbl_peek_front(deque_dbl *d);
bool qdbl_push_front(deque_dbl *d, double el);
double qdbl_pop_back(deque_dbl *d);
double qdbl_peek_back(deque_dbl *d);
bool qdbl_is_empty(deque_dbl *d);

#endif
