#ifndef ARRAY_H
#define ARRAY_H

#include "io_status.h"
#include "student.h"

io_status read_students (student *arr, int n, const char *name);
void print_students (const student *arr, int n, int p);
int diff_array (const student *arr, const int n);

#endif // ARRAY_H
