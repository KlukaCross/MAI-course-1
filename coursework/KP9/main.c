#include "vitem.h"
#include "user_interface.h"
#include "sort_hoar.h"
#include <stdio.h>

int main() {
    vector_item v;
    vitem_init(&v);
    printf("Input items (key format: A+Bi) (to finish entering items, type \"end\"):\n");
    read_items(&v);
    printf("Items:\n");
    print_items(&v);
    sort_hoar(&v);
    printf("Sorted items:\n");
    print_items(&v);
    printf("Input keys (key format: A+Bi) (to finish entering keys, type \"end\"):\n");
    read_keys(&v);
    vitem_destroy(&v);
    return 0;
}