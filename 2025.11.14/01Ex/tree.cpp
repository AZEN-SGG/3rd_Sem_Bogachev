#include "tree.h"

#include <cstdio>

io_status tree::read (FILE *fp, unsigned int max_read)
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

family tree::find_max_subtree (tree_node *root)
{
	family extr;

	extr.child = root;
	extr.parent = nullptr;
	extr.dir = 0;

	for (tree_node *curr = root ; (curr != nullptr) ; curr = curr->right)
	{
		tree_node *child = curr->left;
		if (child != nullptr)
		{
			family left_extr = find_max_subtree(child);
			if (*left_extr.child > *extr.child)
			{
				extr = left_extr;
				if (extr.parent == nullptr)
					extr.parent = curr;
			}
		}
		
		child = curr->right;
		if (child != nullptr)
		{
			if (*child > *extr.child)
			{
				extr.child = child;
				extr.parent = curr;
				extr.dir = 1; // Right direction
			}
		}
	}

	return extr;
}

