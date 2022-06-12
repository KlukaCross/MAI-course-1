#include "ddbl.h"

int main() {
    deque_dbl d;
    ddbl_init(&d);
    ddbl_push_back(&d, 0);
    ddbl_push_back(&d, 1);
    ddbl_push_front(&d, 1);
    ddbl_push_back(&d, 2);
    ddbl_push_front(&d, 2);
    ddbl_push_back(&d, 3);
    ddbl_push_front(&d, 3);
    double a = ddbl_pop_back(&d);
    a = ddbl_pop_front(&d);
    ddbl_destroy(&d);

    return 0;
}
