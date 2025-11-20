#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

int tree::solve1(int k)
    {
    int count = 0, kol = 0;
    tree subtree;
    tree_node* curr;
    
    if (!root) return 0;
    
    for (curr = root->down; curr; curr = curr->level) 
        {
        subtree.root = curr;
        count += subtree.solve1(k);
        kol++;
        }
    
    if (kol == k) count++;
    
    subtree.root = nullptr;
    return count;
    }
