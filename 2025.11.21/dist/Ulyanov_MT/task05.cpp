#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

int tree::solve5(int k)
    {
    int count;
    
    count = this->count_level(k);
    
    return count;
    }
    
int tree::count_level(int i)
    {
    if (!root) return 0;
    if (i == 0) return 1;
    
    int count = 0;
    tree subtree;
    tree_node* curr;
    
    for (curr = root->down; curr; curr = curr->level)
        {
        subtree.root = curr;
        count += subtree.count_level(i - 1);
        }
    
    subtree.root = nullptr;
    return count;
    }

