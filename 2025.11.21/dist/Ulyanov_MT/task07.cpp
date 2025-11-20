#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

int tree::solve7(int k)
    {
    int count;
    if (!root) return 0;
    
    count = this->delete_min(k);
    
    return count;
    }    
    
int tree::delete_min(int k)
    {
    int count = 0;
    tree subtree;
    tree_node* curr;
    tree_node* prev = nullptr;
    tree_node* next;
    if (!root) return 0;
    if (root->get_value() <= k) 
        {
        count += this->get_kount(k);
        delete_subtree(root);
        root = nullptr;
        return count;
        }
    for (curr = root->down; curr; curr = next)
        {
        next = curr->level;
        subtree.root = curr;
        count += subtree.delete_min(k);
        if (!subtree.root) 
            {
            if (!prev) root->down = next;
            else prev->level = next;
            }
        else prev = curr;
        }
    
    subtree.root = nullptr;
    return count;
    }
    
int tree::get_kount(int k)
    {
    int count = 0;
    tree subtree;
    tree_node* curr;
    if (!root) return 0;
    if (root->get_value() <= k) count++;
    
    for (curr = root->down; curr; curr = curr->level)
        {
        subtree.root = curr;
        count += subtree.get_kount(k);
        }
    
    subtree.root = nullptr;
    return count;
    }
