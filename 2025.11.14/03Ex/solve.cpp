#include "tree.h"

family tree::find_absolute_left_subtree (tree_node *curr)
{
    family left;
    left.child = nullptr;

    if (curr == nullptr || curr->left == nullptr)
        return left;

    tree_node *prev = nullptr;
    for (; (curr->left != nullptr) ; prev = curr, curr = curr->left);
    
    if (curr->right == nullptr)
    {
        left.child = curr;
        left.parent = prev;
        left.dir = 0;
    }

    return left;
}

tree_node * tree::balance_to_left_subtree (tree_node *root)
{
    for (tree_node *prev = nullptr, *curr = root ; (curr != nullptr) ; prev = curr, curr = curr->right)
    {
        if (curr->left != nullptr)
            curr->left = balance_to_left_subtree(curr->left);
        else
        {
            family C = find_absolute_left_subtree(curr->right);
            if (C.child == nullptr)
                continue;

            C.parent->left = nullptr;
            
            if (prev == nullptr)
                root = C.child;
            else
                prev->right = C.child;

            C.child->left = curr;
            C.child->right = curr->right;

            curr->right = nullptr;
            curr = C.child;
        }
    }

    return root;
}

void tree::t3_solve ()
{
    root = balance_to_left_subtree(root);
}
