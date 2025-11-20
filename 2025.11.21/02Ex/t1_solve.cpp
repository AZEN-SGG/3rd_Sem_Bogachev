#include "tree.h"

int tree::get_count_subtree_with_k_children (const tree_node *curr, const int k)
{
    if (!curr)
        return 0;

    int count = 0, len = 0;
    for (curr = curr->down ; curr ; curr = curr->level)
    {
        count += get_count_subtree_with_k_children(curr, k);
        len++;
    }

    return count + (len == k);
}

int tree::t1_solve (const int k) const
{
    return get_count_subtree_with_k_children(root, k);
}
