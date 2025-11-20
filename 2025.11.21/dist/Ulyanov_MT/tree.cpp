#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void tree::delete_subtree(tree_node* curr)
    {
    if (curr == nullptr) return;
    tree_node* p;
    tree_node* next;
    for (p = curr->down; p; p = next) {next = p->level; delete_subtree(p);}
    delete curr;
    }
    
void tree::print_subtree(tree_node* curr, int level, int r)
    {
    if (curr == nullptr || level > r) return;
    
    int spaces = level * 2;
    
    for (int i = 0; i < spaces; i++) printf(" ");
    curr->print(stdout);
    for (tree_node* p = curr->down; p; p = p->level) print_subtree(p, level+1, r);
    }
    
void tree::add_node(tree_node* curr, tree_node* x)
    {
    if (curr->down == nullptr) {curr->down = x; return;}
    
    if (*x < *curr)
        {
        if (*curr->down < *curr) add_node(curr->down, x);
        else {x->level = curr->down; curr->down = x;}
        }
    else if (*x == *curr)
        {
        if (curr->down->level != nullptr)
            {
            x->level = curr->down->level;
            curr->down->level = x;
            }
        else if (*curr->down < *curr) curr->down->level = x;
        else
            {
            x->level = curr->down;
            curr->down = x;
            }
        }
    else
        {
        tree_node* p;
        for (p = curr->down; p->level; p = p->level);
        if (*p > *curr) add_node(p, x);
        else p->level = x;
        }
    }
    
io_status tree::read(FILE* fp)
    {
    tree_node x;
    while (x.read(fp) == io_status::success)
        {
        tree_node* curr = new tree_node ((tree_node&&) x);
        if (curr == nullptr) {delete_subtree(root); return io_status::memory;}
        if (root == nullptr) root = curr;
        else
            add_node(root, curr);
        }
    if (!feof(fp))
        {
        delete_subtree(root);
        return io_status::format;
        }
    return io_status::success;
    }
    
io_status read_file(tree* tree, const char* name)
    {
    FILE *fp;
    io_status ret;
    fp = fopen(name, "r");
    if (!fp)
        return io_status::eof;
    ret = tree->read(fp);
    fclose(fp);
    return ret;
    }
