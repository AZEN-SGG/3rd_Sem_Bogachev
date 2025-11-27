#include "tree.h"

int tree::num_level (int level)
{
    int now = 0,
        number = 0;

    tree_node *curr =  nullptr;
    for (curr = root, now = 1 ; (curr != nullptr) && (now < level) ; curr = curr->right, now++)
    {
        tree_node *left = curr->left;
        if (left != nullptr)
        {
            tree temp;
            temp.root = left;
            number += temp.num_level(level - now);
            temp.root = nullptr;
        }
    }

    if ((curr != nullptr) && (level == now))
        number++;

    return number;
}

int tree::t3_solve ()
{
    int max_len = 0,
        len = 0,
        n = 1;

    if (root == nullptr)
        return 0;
    
    max_len = 1;
    len = 1;

    while (len != 0)
    {
        n++;
        len = num_level(n);
        max_len = (max_len < len) ? len : max_len;
    }

    return max_len;
}
