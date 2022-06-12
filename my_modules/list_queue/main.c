#include "qdbl.h"

int main() {
    queue_dbl q;
    qdbl_init(&q);
    qdbl_push(&q, 1);
    qdbl_push(&q, 2);
    qdbl_push(&q, 3);
    double a = qdbl_peek(&q);
    a = qdbl_pop(&q);
    qdbl_push(&q, 4);
    qdbl_destroy(&q);
    return 0;
}
