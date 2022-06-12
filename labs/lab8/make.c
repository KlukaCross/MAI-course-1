#include "make.h"

void make(int max_h, int max_pyr) {
    printf("Start make %s version %s\n", NAME, VERSION);
    int h = max_h/max_pyr;
    for (int n=0; n<max_pyr; n++) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < h - i-1; j++) {
                printf(" ");
            }
            for (int j = 0; j < 2 * i + 1; j++) {
                printf("*");
            }
            printf("\n");
        }
    }
    printf("End make %s\n", NAME);
}
