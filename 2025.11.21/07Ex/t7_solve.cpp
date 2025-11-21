#include "tree.h"

int tree::get_count_nodes_with_value_less_k (const tree_node *curr, const int k)
{
    int count = 0;

    count += (curr->value <= k);
    for (curr = curr->down ; curr ; curr = curr->level)
        count += get_count_nodes_with_value_less_k(curr, k);

    return count;
}

int tree::delete_subtrees_with_value_less_k (tree_node *root, const int k)
{
    int count = 0;
    tree_node *prev = nullptr,
              *curr = nullptr,
              *next = nullptr;
    for (curr = root->down ; curr ; prev = curr, curr = next)
    {
        next = curr->level;
        
        if (curr->value <= k)
        {
            count += get_count_nodes_with_value_less_k(curr, k);

            if (!prev)
                root->down = next;
            else
                prev->level = next;
            
            delete_subtree(curr);
            curr = prev;
        } else
            count += delete_subtrees_with_value_less_k(curr, k);
    }
    
    return count;
}

int tree::t7_solve (const int k)
{
    if (!root)
        return 0;

    if (root->value <= k)
    {
        int count = get_count_nodes_with_value_less_k(root, k);
        delete_subtree(root);
        root = nullptr;
        return count;
    }

    return delete_subtrees_with_value_less_k(root, k);
}

