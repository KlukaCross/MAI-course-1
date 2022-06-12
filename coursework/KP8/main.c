#include "user_interface.h"
#include "list.h"

int main() {
    barrier_list lst;
    list_init(&lst);
    print_help();
    loop(&lst);
    list_destroy(&lst);
    return 0;
}
