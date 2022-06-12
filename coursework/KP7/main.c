#include <stdio.h>
#include "svdbl.h"
#include "svint.h"

typedef struct {
    svector_int lb;
    svector_dbl ye;
    int m;
    int n;
} matrix;

matrix read_matrix() {
    matrix res;
    int m, n;
    scanf("%d%d", &m, &n);
    res.m = m;
    res.n = n;
    svint_init(&res.lb);
    svdbl_init(&res.ye);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            double a;
            scanf("%lf", &a);
            if (a != 0) {
                svdbl_push_back(&res.ye, a);
                svint_push_back(&res.lb, i*n+j);
            }
        }
    }
    return res;
}

void print_matrix(matrix *matr) {
    int cur = 0;
    for (int i = 0; i < matr->m; i++) {
        for (int j = 0; j < matr->n; j++) {
            if (cur < svint_get_size(&matr->lb) && i*matr->n + j == svint_get(&matr->lb, cur)) {
                printf("%lf", svdbl_get(&matr->ye, cur));
                cur++;
            } else {
                printf("%lf", 0.);
            }
        }
        printf("\n");
    }
}

svector_dbl read_vector(int n) {
    svector_dbl res;
    svdbl_init(&res);
    for (int i = 0; i < n; i++) {
        double a;
        scanf("%lf", &a);
        svdbl_push_back(&res, a);
    }
    return res;
}

svector_dbl dot(svector_dbl *vec, matrix *matr) {
    svector_dbl res;
    svdbl_init(&res);
    svdbl_set_size(&res, matr->m);
    for (int cur = 0; cur < svint_get_size(&matr->lb); cur++) {
        int k = svint_get(&matr->lb, cur);
        int j = k % matr->n;
        svdbl_set(&res, j, svdbl_get(&res, j)+svdbl_get(vec, j)*svdbl_get(&matr->ye, cur));
    }
    return res;
}

int get_number_nonull(svector_dbl *vec) {
    int res = 0;
    for (int i = 0; i < svdbl_get_size(vec); i++) {
        if (svdbl_get(vec, i) != 0) res++;
    }
    return res;
}

int main() {
    matrix matr = read_matrix();
    svector_dbl vec = read_vector(matr.m);
    svector_dbl new_vec = dot(&vec, &matr);
    printf("%d", get_number_nonull(&new_vec));
    return 0;
}
