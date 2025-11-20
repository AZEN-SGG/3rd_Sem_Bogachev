#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

int tree::solve6(int k, int* ret)
    {
    int count = 0, maxlev = 0, lev = 0;
    tree subtree;
    tree_node* curr;
    if (!root) return 0;
    
    for (curr = root->down; curr; curr = curr->level)
        {
        subtree.root = curr;
        count += subtree.solve6(k - 1, &lev);
        if (lev > maxlev) maxlev = lev;
        }
    if (maxlev >= k - 1) count++;
    if (ret) *ret = maxlev + 1;
    subtree.root = nullptr;
    return count;
    }
    
int tree::get_level()
    {
    int count = 0, tmp;
    tree_node* curr;
    tree subtree;
    if (!root) return 0;
    
    for (curr = root->down; curr; curr = curr->level)
        {
        subtree.root = curr;
        tmp = subtree.get_level();
        count = (count > tmp ? count : tmp);
        }
    
    subtree.root = nullptr;
    return count + 1;
    }
