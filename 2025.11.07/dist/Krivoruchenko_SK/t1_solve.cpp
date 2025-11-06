#include "tree.h"

int tree::t1_solve ()
{
    int count = 0,
        is_end = 0;

    tree_node* curr = nullptr;
    for (curr = root ; (curr != nullptr) ; curr = curr->right)
    {
        is_end = 0;

        tree_node *left = curr->left;
        if (left != nullptr)
        {
            tree temp;
            temp.root = left;
            count += temp.t1_solve();
            temp.root = nullptr;
        } else
            is_end++;
    }

    count += is_end;

    return count;
}
