#include "qdbl.h"

void qdbl_init(queue_dbl *q, char * name) {
    q->size = 0;
    q->first = 0;
    q->buf = fopen(name, "w+");
}

void qdbl_destroy(queue_dbl *q) {
    q->size = 0;
    q->first = 0;
    fclose(q->buf);
}

bool qdbl_push(queue_dbl *q, double el) {
    if (fseek(q->buf, (q->size+q->first)*sizeof(double), SEEK_SET)) return false;
    if (!fwrite(&el, sizeof(double), 1, q->buf)) return false;
    q->size++;
    return true;
}

double qdbl_pop(queue_dbl *q) {
    double res;
    fseek(q->buf, q->first*sizeof(double), SEEK_SET);
    fread(&res, sizeof(double), 1, q->buf);
    q->first++;
    q->size--;
    return res;
}
double qdbl_peek(queue_dbl *q) {
    double res;
    fseek(q->buf, q->first*sizeof(double), SEEK_SET);
    fread(&res, sizeof(double), 1, q->buf);
    return res;
}

bool qdbl_is_empty(queue_dbl *q) {
    return q->size == 0;
}

