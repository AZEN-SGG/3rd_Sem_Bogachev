#include "tree.h"

int tree::t5_solve (const int k) const
{
    if (!root)
        return 0;

    return get_count_nodes_on_level_subtree(root, k, 0);
}

