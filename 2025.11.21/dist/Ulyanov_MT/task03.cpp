#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

int tree::solve3(int k, int* ret_lev, int* ret_len)
    {
    int count = 0, kol = 0, amount = 0, lev = 0, maxlev = 0, len = 0;
    tree subtree;
    tree_node* curr;
    if (!root) return 0;
    amount++;
    
    for (curr = root->down; curr; curr = curr->level)
        {
        subtree.root = curr;
        kol = subtree.solve3(k, &lev, &len);
        if (lev > maxlev) maxlev = lev;
        count += kol;
        amount += len;
        }
        
    if (maxlev < k) count = amount;
    subtree.root = nullptr;
    if (ret_lev) *ret_lev = maxlev + 1;
    if (ret_len) *ret_len = amount;
    return count;
    }
    
int tree::get_level_and_count(int* lev_ret)
    {
    int count = 0, maxlev = 0, lev = 0;
    tree subtree;
    tree_node* curr;
    if (!root) {*lev_ret = 0; return 0;}
    
    for (curr = root->down; curr; curr = curr->level)
        {
        subtree.root = curr;
        count += subtree.get_level_and_count(&lev);
        if (lev > maxlev) maxlev = lev;
        }
    *lev_ret = maxlev + 1;
    subtree.root = nullptr;
    return count + 1;
    }
