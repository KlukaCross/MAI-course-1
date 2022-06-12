#include <stdio.h>
#include "qdbl.h"

int main() {
    queue_dbl q;
    qdbl_init(&q, "text.txt");
    qdbl_push(&q, 1);
    qdbl_push(&q, 2);
    qdbl_push(&q, 3);
    qdbl_push(&q, 4);
    double a = qdbl_pop(&q);
    a = qdbl_pop(&q);
    a = qdbl_peek(&q);
    return 0;
}
