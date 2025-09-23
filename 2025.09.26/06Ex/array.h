#ifndef ARRAY_H
#define ARRAY_H

#include "io_status.h"
#include "data.h"

io_status read_array (data *arr, int n, const char *name);
void print_array (const data *arr, int n, int m);
int diff_array (const data *arr, const int n);

#endif
