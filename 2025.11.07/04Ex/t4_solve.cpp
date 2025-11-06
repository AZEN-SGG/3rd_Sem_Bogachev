#include "tree.h"

// A non-null tree is assumed
int tree::depth_tree (int *max_diff)
{
    tree tmp;
    int max_depth = 1;

    int left_level = 0;
    tree_node *child = root->left;
    if (child != nullptr)
    {
        tmp.root = child;
        left_level = tmp.depth_tree(max_diff);
        tmp.root = nullptr;
    }

    int right_level = 0;
    child = root->right;
    if (child != nullptr)
    {
        tmp.root = child;
        right_level = tmp.depth_tree(max_diff);
        tmp.root = nullptr;
    }

    int diff = 0;
    if (right_level < left_level)
    {
        diff = left_level - right_level;
        max_depth += left_level;
    } else
    {
        diff = right_level - left_level;
        max_depth += right_level;
    }
    
    *max_diff = (*max_diff < diff) ? diff : *max_diff;

    return max_depth; 
}

int tree::t4_solve ()
{
    int max_diff = 0;
    
    if (root == nullptr)
        return 0;

    depth_tree(&max_diff);

    return max_diff;
}
