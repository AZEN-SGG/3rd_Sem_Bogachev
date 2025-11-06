#include "tree.h"

int tree::t2_solve ()
{
    int max_len = 0,
        len = 0;

    tree_node* curr = nullptr;
    for (curr = root ; (curr != nullptr) ; curr = curr->right)
    {
        len++;

        tree_node *left = curr->left;
        if (left != nullptr)
        {
            tree temp;
            temp.root = left;
            int temp_len = len + temp.t2_solve();
            temp.root = nullptr;

            max_len = (max_len < temp_len) ? temp_len : max_len;
        }
    }

    max_len = (max_len < len) ? len : max_len;

    return max_len;
}
