#include "tree.h"

#include <cstdio>

io_status tree::read (FILE *fp, const unsigned int max_read)
{
    tree_node x;
    io_status ret;

    if (x.read(fp) != (ret = io_status::success))
        return ret;

    root = new tree_node((tree_node&&)x);
    if (root == nullptr)
        return io_status::memory;

    unsigned int readed = 1;
    while ((x.read(fp) == io_status::success) && (readed < max_read))
    {
        tree_node *curr = new tree_node((tree_node&&)x);
        if (curr == nullptr)
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

io_status tree::read_file (char *filename, unsigned int max_read)
{
    FILE *fp = fopen(filename, "r");
    if (fp == nullptr)
        return io_status::open;

    io_status ret = read(fp, max_read);

    fclose(fp);
    return ret;
}

