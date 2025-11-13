#include "tree.h"

#include <cstring>

int tree::delete_subtree_with_k_arm (tree_node *root, const student& x)
{
    int left    = 0,
        right   = 0,
        cmp = strstr(root->name, x.name) != nullptr;
    
    if (root->left != nullptr)
            left = delete_subtree_with_k_arm(root->left, x);

    if (root->right != nullptr)
            right = delete_subtree_with_k_arm(root->right, x);
    
    if (right > 0 || left > 0)
    {
        if (cmp)
            return (right > left ? right : left) + 1;
        
        if (right >= x.value)
        {
            delete_subtree(root->right);
            root->right = nullptr;
        }
        if (left >= x.value)
        {
            delete_subtree(root->left);
            root->left = nullptr;
        }

        return -1;
    } else if (right < 0 || left < 0 || (!cmp))
        return -1;
    else
        return 1;
}

void tree::t6_solve (const student& x)
{
    if ((root != nullptr) && delete_subtree_with_k_arm(root, x) >= x.value)
    {
        delete_subtree(root);
        root = nullptr;
    }
}
