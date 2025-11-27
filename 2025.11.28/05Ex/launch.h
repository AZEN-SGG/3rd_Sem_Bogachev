#ifndef LAUNCH_H
#define LAUNCH_H

#include "io_status.h"
#include "tree.h"

#include <ctime>
#include <new>

template <typename T>
int launch (char * path, char * filename, int r = 10, int m = 0);

#endif // LAUNCH_H
