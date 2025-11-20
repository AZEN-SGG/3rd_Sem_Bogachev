#include "solve.h"

t_count tree::get_count_nodes_in_subtree_less_k (const tree_node *curr, const int k)
{
    if (!curr)
        return {0, 0};

    t_count answer = {0, 0};

    for (curr = curr->down ; curr ; curr = curr->level)
        answer += get_count_nodes_in_subtree_less_k(curr, k);

    answer.count++;
    if (answer.count <= k)
        answer.need++;

    return answer;
}

int tree::t2_solve (const int k) const
{
    return get_count_nodes_in_subtree_less_k(root, k).need;
}

