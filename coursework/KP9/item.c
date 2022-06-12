#include "item.h"

int key_cmp(__complex128 key1, __complex128 key2) {
    return (crealq(key1) != crealq(key2))?
           (int) (crealq(key1) - crealq(key2)) :
           (int) (cimagq(key1) - cimagq(key2));
}
