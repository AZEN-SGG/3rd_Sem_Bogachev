#ifndef LAUNCH_H
#define LAUNCH_H

#include "io_status.h"
#include "student.h"
#include "b_tree.h"

#include <ctime>
#include <new>

template <typename T>
int launch (char * path, char * filename, const int m, const int k, int r = 10);

#endif // LAUNCH_H
