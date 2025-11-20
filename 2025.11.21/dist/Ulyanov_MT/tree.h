#include "student.h"
#ifndef tree_H
#define tree_H
#include <stdio.h>
#include <string.h>

class tree;

class tree_node : public student
    {
    private:
        tree_node* down = nullptr;
        tree_node* level = nullptr;
    public:
        tree_node() = default;
        tree_node(const tree_node& x) = delete;
        tree_node(tree_node&& r):student((student&&) r)
            {
            erase_links();
            r.erase_links();
            }
        ~tree_node() {erase_links();}
        tree_node& operator= (const tree_node&) = delete;
        tree_node& operator= (tree_node&& r)
            {
            if (this == &r) return *this;
            (student&&) *this = (student&&) r;
            erase_links(); r.erase_links();
            return *this;
            }
        friend class tree;
    private:
        void erase_links() {down = nullptr; level = nullptr;}
    };
    
class tree
    {
    private:
        tree_node* root = nullptr;
    public:
        tree() = default;
        tree(const tree& x) = delete;
        tree(tree&& x) {root = x.root; x.root = nullptr;}
        ~tree() {delete_subtree(root); root = nullptr;}
        
        tree& operator= (const tree& x) = delete;
        tree& operator= (tree&& x)
            {
            if (this == &x) return *this;
            delete_subtree(root);
            root = x.root; x.root = nullptr;
            return *this;
            }
        int solve1(int);
        int solve2(int, int* ret = nullptr);
        int solve3(int, int* ret_lev = nullptr, int* ret_len = nullptr);
        int solve4(int, int* ret_len = nullptr);
        int solve5(int);
        int solve6(int, int* ret = nullptr);
        int solve7(int);
        int get_count();
        int get_level();
        int get_level_and_count(int*);
        int count_level_and_amount(int, int*);
        int count_level(int);
        int get_kount(int);
        int delete_min(int);
        void print(int r) const
            {print_subtree(root, 0, r);}
        io_status read(FILE* fp);
    private:
        static void delete_subtree(tree_node* curr);
        static void print_subtree(tree_node* curr, int level, int r);
        static void add_node(tree_node* curr, tree_node* x);
    };
    
#endif

io_status read_file(tree*, const char*);
    
