#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

int tree::solve2(int k, int* ret)
    {
    int count = 0, kol = 0, amount = 0, total = 0;
    tree subtree;
    tree_node* curr;
    if (!root) return 0;
    amount++;
    
    for (curr = root->down; curr; curr = curr->level)
        {
        subtree.root = curr;
        kol = subtree.solve2(k, &total);
        count += kol;
        amount += total;
        }
    if (amount <= k) count = amount;
    subtree.root = nullptr;
    if (ret) *ret = amount;
    return count;
    }
    
int tree::get_count()
    {
    int count = 0;
    tree_node* curr;
    tree subtree;
    if (!root) return 0;
    
    for (curr = root->down; curr; curr = curr->level)
        {
        subtree.root = curr;
        count += subtree.get_count();
        }
    
    subtree.root = nullptr;
    return count + 1;
    }
