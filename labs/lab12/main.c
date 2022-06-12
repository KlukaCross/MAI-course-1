#include <stdio.h>

int abs(int a) {
    if (a < 0) return -a;
    return a;
}

int ipow(int a, int n) {
    int res = 1;
    for (int i = 0; i < n; i++) {
        res *= a;
    }
    return res;
}

int func(int inp) {
    int res=0, a=-1, cnt=0, flg=1;
    if (inp<0) {
        flg = -1;
        inp = abs(inp);
    }
    while (inp) {
        res = ipow(10, cnt) * (inp % 10) + res;
        if (a == -1) {
            a = inp % 10;
        }
        else {
            cnt++;
            res = ipow(10, cnt) * abs(a - inp%10) + res;
            a = -1;
        }
        cnt++;
        inp /= 10;
    }
    return res*flg;
}

int main() {
    int inp;
    while (scanf("%d", &inp) != EOF) {
        printf("%d\n", func(inp));
    }
    return 0;
}

