#include "tree.h"

#include <cstring>

int tree::delete_k_deep_subtrees_with_s (tree_node *root, const student &x)
{
    int deep;


    int child_deep = -1;
    if (root->left != nullptr)
        child_deep = delete_k_deep_subtrees_with_s(root->left, x);

    deep = child_deep;

    if (root->right != nullptr)
        child_deep = delete_k_deep_subtrees_with_s(root->right, x);
    
    int cmp = strstr(root->name, x.name) != nullptr;
    if ((deep < 0) && (child_deep < 0) && cmp)
    {
        deep = 1;
    } else if ((deep != 0) && (child_deep != 0) && cmp)
    {
        deep = ((child_deep < deep) ? deep : child_deep) + 1;
    } else
    {
        if (deep >= x.value)
        {
            delete_subtree(root->left);
            root->left = nullptr;
        }
        if (child_deep >= x.value)
        {
            delete_subtree(root->right);
            root->right = nullptr;
        }

        deep = 0;
    }

    return deep;
}

void tree::t5_solve (const student& x)
{
    if ((root != nullptr) && delete_k_deep_subtrees_with_s(root, x) >= x.value)
    {
        delete_subtree(root);
        root = nullptr;
    }
}
