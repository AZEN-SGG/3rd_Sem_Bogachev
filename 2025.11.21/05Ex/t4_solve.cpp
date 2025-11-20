#include "tree.h"

int tree::get_count_nodes_on_level_subtree (const tree_node *curr, const int n, const int level)
{
    int count = 0;

    if (level == n)
        return 1;

    for (curr = curr->down ; curr ; curr = curr->level)
        count += get_count_nodes_on_level_subtree (curr, n, level + 1);

    return count;
}

int tree::get_count_nodes_in_subtree_with_less_k_on_level (const tree_node *curr, const int k, const int c_level)
{
    int n_level = c_level, // need level
        count = 0, // count nodes
        nodes = 0; // count nodes on the n level on this subtree

    do {
        nodes = get_count_nodes_on_level_subtree(curr, n_level, c_level);
        count += nodes;
        n_level++;
    } while (nodes && (nodes <= k));

    if (!nodes)
        return count;

    count = 0;
    n_level = c_level + 1;

    for (curr = curr->down ; curr ; curr = curr->level, n_level++)
        count += get_count_nodes_in_subtree_with_less_k_on_level(curr, k, n_level);

    return count;
}

int tree::t4_solve (const int k) const
{
    if (!root)
        return 0;

    return get_count_nodes_in_subtree_with_less_k_on_level(root, k, 0);
}

