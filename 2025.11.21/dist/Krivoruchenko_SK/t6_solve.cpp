#include "tree.h"

int tree::get_count_nodes_in_branch_above_k (const tree_node *curr, const int k, const int level)
{
    int count = 0;

    for (curr = curr->down ; curr ; curr = curr->level)
        count += get_count_nodes_in_branch_above_k(curr, k, level + 1);
    
    count += (count > 0 || level >= k);

    return count;
}

int tree::t6_solve (const int k) const
{
    if (!root)
        return 0;

    return get_count_nodes_in_branch_above_k(root, k, 1);
}

