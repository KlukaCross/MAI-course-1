#ifndef INTERFACE_H
#define INTERFACE_H

#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "svint.h"

void print_help();
void print_list(barrier_list *l);
void add(barrier_list *l, svector_int *buf);
void del(barrier_list *l, svector_int *buf);
void print_size(barrier_list *l);
void pop(barrier_list *l, int k);
void loop(barrier_list *l);

#endif
