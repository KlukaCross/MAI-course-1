#ifndef SORTING_STATION_H
#define SORTING_STATION_H
#include "error_struct.h"
#include "token_queue.h"
#include "token_stack.h"
#include <string.h>
bool sorting_station(queue_token *infix, queue_token *postfix, error *err);

#endif
