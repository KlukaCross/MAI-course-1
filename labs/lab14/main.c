#include <stdio.h>

void scanMatr(int n, int m, int matr[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matr[i][j]);
        }
    }
}

void printMatr(int n, int matr[n][n]) {
    int c=0, d=0;
    for (int i = 0; i < 2*n-1; i++) {
        for (int j = d; j < c+1; j++) {
            printf("%d ", matr[c-j+d][j]);
        }
        (i < n-1)? c++ : d++;
    }
    printf("\n");
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int matr[n][n];
        scanMatr(n, n, matr);
        printMatr(n, matr);
    }
    return 0;
}
