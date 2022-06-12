#include <stdio.h>
#include <stdbool.h>

typedef unsigned long long int set;

typedef enum {
    BEYOND_WORD,
    IN_WORD
} state;

typedef enum {
    L_A = 1072,
    L_E = 1077,
    L_YO = 1105,
    L_I = 1080,
    L_O = 1086,
    L_Y = 1091,
    L_YY = 1099,
    L_EE = 1101,
    L_U = 1102,
    L_YA = 1103,
    B_YO = 1025
} vowels_rus;

bool is_sep(int c);

int letter_to_index(int c);

set letter_to_set(int c);

bool check_sets(set prev, set current, set vowels);

int index_to_letter(int c);

int getutf8char();

void dis_vowels(set* st, int c, set vowels);

int main() {
    set VOWELS = {letter_to_set(L_A) | letter_to_set(L_E) | letter_to_set(L_YO) | letter_to_set(L_I) |
                  letter_to_set(L_O) | letter_to_set(L_Y) | letter_to_set(L_YY) | letter_to_set(L_EE) |
                  letter_to_set(L_U) | letter_to_set(L_YA)};
    set prev = 0, current = 0;
    int c;
    bool ans = false;
    state st = BEYOND_WORD;
    do {
        c = getutf8char();
        if (ans) continue;
        if (st == BEYOND_WORD) {
            if (c == EOF || is_sep(c)) continue;
            else {
                st = IN_WORD;
                dis_vowels(&current, c, VOWELS);
            }
        }
        else {
            if (c == EOF || is_sep(c)) {
                st = BEYOND_WORD;
                ans = check_sets(prev, current, VOWELS);
                prev = current;
                current = 0;
            }
            else dis_vowels(&current, c, VOWELS);
        }
    }
    while (c != EOF);
    ans ? printf("\nYES\n") : printf("\nNO\n");
    return 0;
}

bool is_sep(int c) {
    return (('\t' <= c && c <= '\r') || c == ' ' || c == ',');
}

int letter_to_index(int c) {
    if (c >= L_A && c <= L_YA) return c - L_A;
    if (c >= L_A-32 && c <= L_YA-32) return c - L_A+32;
    if (c == L_YO || c == B_YO) return 32;
    return -1;
}

set letter_to_set(int c) {
    int idx = letter_to_index(c);
    if (idx == -1) return 0;
    set res = ((set)1) << idx;
    return res;
}

bool check_sets(set prev, set current, set vowels) {
    if (!(prev & vowels)) return false;  // if prev (or current) does not any vowel then false
    return !(prev ^ current);
}

int index_to_letter(int c) {
    if (c >= 0 && c < 32) return c+L_A;
    else if (c == 32) return L_YO;
    return -1;
}

int getutf8char() {
    int c = getchar();
    int d = 128, okt = 0, res;
    if (!(c&d)) return c;
    d = d>>1;
    while (c&d) {
        okt++;
        d>>=1;
    }
    res = c & (d - 1);
    d = 63;
    for (int i=0; i<okt; i++) {
        c = getchar();
        res = (res << 6) | (c & d);
    }
    return res;
}

void dis_vowels(set* st, int c, set vowels) {
    (*st) |= (letter_to_set(c) & vowels);
}