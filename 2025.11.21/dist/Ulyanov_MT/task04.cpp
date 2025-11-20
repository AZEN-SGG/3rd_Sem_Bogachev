#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

int tree::solve4(int k, int* ret_len)
    {
    int i = 0;
    int amount = 0, count = 0, kol = 0, lev = 0, len = 0;
    tree subtree;
    tree_node* curr;
    if (!root) return 0;
    amount++;
    
    while (1)
      {
      lev = this->count_level_and_amount(i, &amount);
      if (lev == 0) break;
      if (lev > k) break;
      i++;
      }
    if (lev == 0) 
        {
        if (ret_len) *ret_len = amount;
        return amount;
        }
    amount = 1;
    
    for (curr = root->down; curr; curr = curr->level)
        {
        subtree.root = curr;
        kol = subtree.solve4(k, &len);
        count += kol;
        amount += len;
        }

    if (ret_len) *ret_len = amount;
    subtree.root = nullptr;
    return count;
    }
    
int tree::count_level_and_amount(int i, int* ret)
    {
    if (!root) return 0;
    if (i == 0) {*ret = 1; return 1;}
    
    int count = 0, amount = 0, len = 0;
    tree subtree;
    tree_node* curr;
    amount++;
    
    for (curr = root->down; curr; curr = curr->level)
        {
        subtree.root = curr;
        count += subtree.count_level_and_amount(i - 1, &len);
        amount += len;
        }
    *ret = amount;
    subtree.root = nullptr;
    return count;
    }

