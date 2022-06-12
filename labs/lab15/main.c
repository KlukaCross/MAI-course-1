#include <stdio.h>

void scanMatr(int n, int m, int matr[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matr[i][j]);
        }
    }
}

void printMatr(int n, int matr[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matr[i][j]);
        }
        printf("\n");
    }
}

int getMultLine(int n, const int line[n]) {
    int res = 1;
    for (int i = 0; i < n; i++) {
        res *= line[i];
    }
    return res;
}

void transformMatr(int n, int matr[n][n]) {
    int min_l=0, max_l=0, min_n=getMultLine(n, matr[0]), max_n=min_n, buff_n;
    for (int i = 1; i < n; i++) {
        buff_n = getMultLine(n, matr[i]);
        if (buff_n >= max_n) {
            max_n = buff_n;
            max_l = i;
        }
        if (buff_n <= min_n) {
            min_n = buff_n;
            min_l = i;
        }
    }
    for (int i = 0; i < n; i++) {
        buff_n = matr[min_l][i];
        matr[min_l][i] = matr[max_l][i];
        matr[max_l][i] = buff_n;
    }
}

int main() {
    int n;
    while ((scanf("%d", &n)) != EOF) {
        int matr[n][n];
        scanMatr(n, n, matr);
        transformMatr(n, matr);
        printMatr(n, matr);
    }
    return 0;
}
