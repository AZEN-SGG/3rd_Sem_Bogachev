#ifndef SOLVE_H
#define SOLVE_H

#include "tree.h"

struct t_count
{
    int need; // What need in task
    int count; // Count of smth, like nodes in subtree

    t_count & operator+= (const t_count &x)
    {
        need += x.need;
        count += x.count;

        return *this;
    }
};

#endif // SOLVE_H
