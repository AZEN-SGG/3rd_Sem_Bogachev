#include "tree.h"

family tree::find_absolute_right_subtree (tree_node *curr)
{
    family right;
    right.child = nullptr;

    if (curr == nullptr || curr->right == nullptr)
        return right;

    tree_node *prev = nullptr;
    for (; (curr->right != nullptr) ; prev = curr, curr = curr->right);
    
    if (curr->left == nullptr)
    {
        right.child = curr;
        right.parent = prev;
        right.dir = 1;
    }

    return right;
}

tree_node * tree::balance_to_right_subtree (tree_node *root)
{
    for (tree_node *prev = nullptr, *curr = root ; (curr != nullptr) ; prev = curr, curr = curr->left)
    {
        if (curr->right != nullptr)
            curr->right = balance_to_right_subtree(curr->right);
        else
        {
            family C = find_absolute_right_subtree(curr->left);
            if (C.child == nullptr)
                continue;

            C.parent->right = nullptr;
            
            if (prev == nullptr)
                root = C.child;
            else
                prev->left = C.child;

            C.child->right = curr;
            C.child->left = curr->left;

            curr->left = nullptr;
            curr = C.child;
        }
    }

    return root;
}

void tree::t4_solve ()
{
    root = balance_to_right_subtree(root);
}
