#include "solve.h"

t_count tree::get_count_nodes_in_subtree_less_k_levels (const tree_node *curr, const int k)
{
    t_count answer = {},
            temp;

    for (curr = curr->down ; curr ; curr = curr->level)
    {
        temp = get_count_nodes_in_subtree_less_k_levels(curr, k);

        answer.need += temp.need;
        answer.count = (answer.count < temp.count) ? temp.count : answer.count;
    }

    answer.count++;
    if (answer.count <= k)
    {
        answer.need++;
    }

    return answer;
}

int tree::t3_solve (const int k) const
{
    if (!root)
        return 0;

    return get_count_nodes_in_subtree_less_k_levels(root, k).need;
}

