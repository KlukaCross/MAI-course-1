#include <stdio.h>
#include <stdbool.h>

typedef enum {
    STATE_FIND_FIRST_DIGIT,
    STATE_FIND_DIGIT_I_POINT,
    STATE_FIND_DIGIT_I,
    STATE_FIND_N,
    STATE_FIND_SEP,
    STATE_ERROR_WORD
} state;

void plus_digit(double *n, int digit, bool point_exists, int *len_after_point);

double dpow(double n, int base);

double calc_mm(double n_in);

void print_res(double n_in);

bool is_sep(char ch);

bool is_digit(char ch);

void break_n(double *n, bool *point_exists, int *len_after_point);

int get_int_digit(char digit);

int main() {
    double n = 0;
    bool point_exists = false;
    int len_after_point = 0;
    state st = STATE_FIND_FIRST_DIGIT;
    int s;
    char ch;
    do {
        s = getchar();
        if (s != EOF) ch = s;
        if ((s == EOF || is_sep(ch)) && (st != STATE_FIND_SEP)) {
            st = STATE_FIND_FIRST_DIGIT;
            break_n(&n, &point_exists, &len_after_point);
            continue;
        }
        if (st == STATE_FIND_FIRST_DIGIT) {
            if (is_digit(ch)) {
                st = STATE_FIND_DIGIT_I_POINT;
                plus_digit(&n, get_int_digit(ch), point_exists, &len_after_point);
            }
            else st = STATE_ERROR_WORD;
        }
        else if (st == STATE_FIND_DIGIT_I_POINT) {
            if (ch == '.') {
                st = STATE_FIND_DIGIT_I;
                point_exists = true;
            } else if (ch == 'i') st = STATE_FIND_N;
            else if (is_digit(ch)) plus_digit(&n, get_int_digit(ch), point_exists, &len_after_point);
            else st = STATE_ERROR_WORD;
        }
        else if (st == STATE_FIND_DIGIT_I) {
            if (ch == 'i') st = STATE_FIND_N;
            else if (is_digit(ch)) plus_digit(&n, get_int_digit(ch), point_exists, &len_after_point);
            else st = STATE_ERROR_WORD;
        }
        else if (st == STATE_FIND_N) {
            if (ch == 'n') st = STATE_FIND_SEP;
            else st = STATE_ERROR_WORD;
        }
        else if (st == STATE_FIND_SEP) {
            if (s == EOF || is_sep(ch)) {
                st = STATE_FIND_FIRST_DIGIT;
                print_res(n);
                break_n(&n, &point_exists, &len_after_point);
            }
            else st = STATE_ERROR_WORD;
        }
    }
    while (s != EOF);
    printf("\n");
    return 0;
}

void plus_digit(double *n, int digit, bool point_exists, int *len_after_point) {
    if (point_exists) {
        (*len_after_point)++;
        *n = *n + dpow(0.1, *len_after_point)*digit;
        return;
    }
    else *n = 10*(*n) + digit;
}

double dpow(double n, int base) {
    double res = 1;
    for (int i = 0; i < base; i++) {
        res *= n;
    }
    return res;
}

double calc_mm(double n_in) {
    return n_in*25.4;
}

void print_res(double n_in) {
    printf("\n%gin -> %gmm\n", n_in, calc_mm(n_in));
}

bool is_sep(char ch) {
    return (('\t' <= ch && ch <= '\r') || ch == ' ');
}

bool is_digit(char ch) {
    return ('0' <= ch && ch <= '9');
}

void break_n(double *n, bool *point_exists, int *len_after_point) {
    *n = 0;
    *point_exists = false;
    *len_after_point = 0;
}

int get_int_digit(char digit) {
    return digit - '0';
}
