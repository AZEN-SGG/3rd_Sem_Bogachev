#include "tree.h"

#include <cstdio>

template <typename T>
io_status tree<T>::read (FILE *fp, unsigned int max_read)
{
    tree_node<T> x;
    io_status ret;

    if (x.read(fp) != (ret = io_status::success))
        return ret;

    root = new tree_node<T>((tree_node<T>&&)x);
    if (!root)
        return io_status::memory;

    unsigned int readed = 1;
    while ((x.read(fp) == io_status::success) && (readed < max_read))
    {
        tree_node<T> *curr = new tree_node<T>((tree_node<T>&&)x);
        if (!curr)
        {
            delete_subtree(root);
            return io_status::memory;
        }

        add_node_subtree(root, curr);
        readed++;
    } if ((!feof(fp)) && (readed < max_read))
    {
        delete_subtree(root);
        return io_status::format;
    }

    return io_status::success;
}

