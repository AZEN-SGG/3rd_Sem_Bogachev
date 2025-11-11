#include "tree.h"

// root is non-nullptr
int tree::find_min ()
{
    int min_val = root->value;

    tree_node *curr = nullptr;
    for (curr = root ; (curr != nullptr) ; curr = curr->right)
    {
        if (curr->value < min_val)
            min_val = curr->value;

        tree_node *left = curr->left;
        if (left != nullptr)
        {
            tree tmp;
            tmp.root = left;
            int min_left = tmp.find_min();
            min_val = (min_left < min_val) ? min_left : min_val;
            tmp.root = nullptr;
        }
    }

    return min_val;
}

int tree::del_with_value (const int value)
{
    int deleted = 0;

    tree_node *parent = nullptr,
              *curr = nullptr,
              *child = nullptr;
    for (curr = root ; (curr != nullptr) ; parent = curr, curr = child)
    {
        child = nullptr;

        if (curr->value == value)
        {
            deleted++;
            delete_subtree(curr);
            if (parent == nullptr)
                root = nullptr;
            else
                parent->right = nullptr;
        } else
        {
            child = curr->left;
            if (child != nullptr)
            {
                tree tmp;
                tmp.root = child;
                deleted += tmp.del_with_value(value);
                if (tmp.root == nullptr)
                    curr->left = nullptr;
                else
                    tmp.root = nullptr;
            }

            child = curr->right;
        }
    }

    return deleted;
}

int tree::t6_solve ()
{
    int deleted = 0;

    if (root == nullptr)
        return 0;

    int min_val = find_min();
    deleted = del_with_value(min_val);

    return deleted;
}
