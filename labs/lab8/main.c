#include "make.h"

int main() {
    int max_height = 10;
    int num_pyramids = 2;
    if (num_pyramids <= 0) {
        printf("num_pyramids must be > 0\n");
        return 0;
    }
    make(max_height, num_pyramids);
    return 0;
}

