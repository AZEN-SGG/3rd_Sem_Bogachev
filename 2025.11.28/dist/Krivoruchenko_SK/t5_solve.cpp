#include "tree.h"

int tree::t5_solve ()
{
    int count = 0;
    
    tree_node *curr = nullptr,
              *child = nullptr;
    for (curr = root ; (curr != nullptr) ; curr = child)
    {
        tree_node *right = curr->right;

        child = curr->left;
        if ((child != nullptr) && (right != nullptr))
        {
            tree tmp;
            tmp.root = child;
            count += tmp.t5_solve();
            tmp.root = nullptr;

            child = right;
        } else if (child != nullptr)
            count++;
        else if (right != nullptr)
        {
            count++;
            child = right;
        }
    }

    return count;
}
