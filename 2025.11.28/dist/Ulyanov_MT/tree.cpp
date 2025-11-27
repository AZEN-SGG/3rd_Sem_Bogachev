#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io_status.h"
#include "tree.h"

template <class T>
io_status read_file(tree<T>* tree, const char* name)
    {
    FILE *fp;
    io_status ret;
    fp = fopen(name, "r");
    if (!fp)
        return io_status::eof;
    ret = tree->read(fp);
    fclose(fp);
    return ret;
    }
