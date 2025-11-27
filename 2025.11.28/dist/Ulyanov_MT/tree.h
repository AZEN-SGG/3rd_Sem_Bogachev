#ifndef tree_H
#define tree_H
#include <stdio.h>
#include <string.h>
#include "student.h"
#include "list.h"

template <class T> class tree;

template <class T> class tree_node : public T
    {
    private:
        tree_node* left = nullptr;
        tree_node* right = nullptr;
    public:
        tree_node() = default;
        tree_node(const tree_node& x) = delete;
        tree_node(tree_node&& r):T((T&&) r)
            {
            erase_links();
            r.erase_links();
            }
        ~tree_node() {erase_links();}
        tree_node& operator= (const tree_node&) = delete;
        tree_node& operator= (tree_node&& r)
            {
            if (this == &r) return *this;
            (T&&) *this = (T&&) r;
            erase_links(); r.erase_links();
            return *this;
            }
        friend class tree<T>;
    private:
        void erase_links() {left = nullptr; right = nullptr;}
    };
    
template <class T>
class tree
    {
    private:
        tree_node<T>* root = nullptr;
    public:
        tree() = default;
        tree(const tree& x) = delete;
        tree(tree&& x) {root = x.root; x.root = nullptr;}
        ~tree()
            {
            delete_subtree(root);
            root = nullptr;
            }
        tree& operator= (const tree& x) = delete;
        tree& operator= (tree&& x)
            {
            if (this == &x) return *this;
            delete_subtree(root);
            root = x.root; x.root = nullptr;
            return * this;
            }
            
        int solve1()
            {
            int count_l = 0, count_r = 0;
            tree<T> subtree_l;
            tree<T> subtree_r;
            if (!root) return 0;
            if ((!(root->left)) && (!(root->right))) return root->get_length();
            if (root->left) {subtree_l.root = root->left; count_l = subtree_l.solve1();}
            if (root->right) {subtree_r.root = root->right; count_r = subtree_r.solve1();}
            subtree_l.root = nullptr;
            subtree_r.root = nullptr;
            return count_l + count_r;
            }
            
        int solve2()
            {
            int len;
            int max = 0;
            int max_l = 0, max_r = 0;
            tree<T> subtree_l;
            tree<T> subtree_r;
            if (!root) return 0;
            len = root->get_length();
            if ((!root->left) && (!root->right)) return len;
            if (root->left) {subtree_l.root = root->left; max_l = subtree_l.solve2();}
            if (root->right) {subtree_r.root = root->right; max_r = subtree_r.solve2();}
            max = (max_l > max_r ? max_l : max_r) + len;
            subtree_l.root = nullptr;
            subtree_r.root = nullptr;
            return max;
            }
            
        int solve3()
            {
            int count = -1, level = 0, max = 0;
            while (count != 0)
                {
                count = subcount(root, level);
                if (count > max) max = count;
                level++;
                }
            return max;
            }
            
        int solve4(int* ret = nullptr)
            {
            int len = 0, max_l = 0, max_r = 0, count = 0, max = 0, count_total = 0, count_l = 0, count_r = 0;
            tree<T> subtree_l, subtree_r;
            if (!root) return 0;
            len = root->get_length();
            
            subtree_l.root = root->left;
            subtree_r.root = root->right;
            
            max_l = subtree_l.solve4(&count_l);
            max_r = subtree_r.solve4(&count_r); 
            count = abs(count_l - count_r);
            
            if ((max_l >= max_r) && (max_l >= count)) max = max_l;
            else if ((max_r >= max_l) && (max_r >= count)) max = max_r;
            else max = count;
            
            count_total = count_l + count_r + len;
            if (ret) *ret = count_total;
            subtree_l.root = nullptr;
            subtree_r.root = nullptr;
            return max;
            }
            
        int solve5()
            {
            int count = 0, ret = 0;
            tree<T> subtree_l, subtree_r;
            if (!root) return count;
            if ((!(root->left)) && (!(root->right))) return 0;
            if (root->left && (!(root->right))) count += root->get_length();
            if (root->right && (!(root->left))) count += root->get_length();
            subtree_l.root = root->left;
            subtree_r.root = root->right;
            ret = subtree_l.solve5() + subtree_r.solve5();
            subtree_l.root = nullptr;
            subtree_r.root = nullptr;
            return count + ret;
            }
            
        int solve6()
            {
            int count = 0;
            int min = root->get_value();
            if (!root) return 0;
            min = (this)->find_min();
            count = (this)->delete_min(min);
            return count;
            }
        
        int find_min()
            {
            int min, min_l, min_r;
            tree<T> subtree_l, subtree_r;
            min = root->get_value();
            if (root->left) {subtree_l.root = root->left;  min_l = subtree_l.find_min(); min = (min < min_l ? min : min_l);}
            if (root->right) {subtree_r.root = root->right; min_r = subtree_r.find_min(); min = (min < min_r ? min : min_r);}
            subtree_l.root = nullptr;
            subtree_r.root = nullptr;
            return min;
            }
            
        int delete_min(int min)
            {
            int count = 0;
            tree<T> subtree_l, subtree_r;
            if (!root) return 0;
            if (root->get_value() == min) {delete_subtree(root); root = nullptr; count++; return count;}
            subtree_l.root = root->left;
            subtree_r.root = root->right;
            count += subtree_l.delete_min(min);
            count += subtree_r.delete_min(min);
            if (!subtree_l.root) root->left = nullptr;
            if (!subtree_r.root) root->right = nullptr;
            subtree_l.root = nullptr;
            subtree_r.root = nullptr;
            return count;
            }
            
        void print(unsigned int r = 10, FILE *fp = stdout) const {print_subtree(root, 0, r, fp);}
        
        io_status read(FILE* fp = stdin, unsigned int max_read = -1)
            {
            unsigned int len = 0;
            tree_node<T> x;
            while ((len < max_read) && (x.read(fp) == io_status::success))
                {
                tree_node<T>* curr = new tree_node<T> ((tree_node<T>&&) x);
                if (curr == nullptr) {delete_subtree(root); return io_status::memory;}
                if (root == nullptr) root = curr;
                else
                    add_node(root, curr);
                len++;
                }
            if (!feof(fp))
                {
                delete_subtree(root);
                return io_status::format;
                }
            return io_status::success;
            }
            
    private:
        static void delete_subtree(tree_node<T>* curr)
            {
            if (curr == nullptr) return;
            delete_subtree(curr->left);
            delete_subtree(curr->right);
            delete curr;
            }
        static void add_node(tree_node<T>* curr, tree_node<T>* x)
            {
            if (*x < *curr)
                {
                if (curr->left == nullptr) curr->left = x;
                else add_node(curr->left, x);
                }
            else
                {
                if (curr->right == nullptr) curr->right = x;
                else add_node(curr->right, x);
                }
            }
        static void print_subtree(tree_node<T>* curr, int level, int max_level, FILE* fp = stdout)
            {
            int spaces = 2 * level;
            if (curr == nullptr || level > max_level) return;
            curr->print(fp, spaces);
            print_subtree(curr->left, level+1, max_level, fp);
            print_subtree(curr->right, level+1, max_level, fp);
            }
        static int subcount(tree_node<T>* root, int level)
            {
            int count_l = 0, count_r = 0;
            if (!root) return 0;
            if (level == 0) return root->get_length();
            count_l = subcount(root->left, level-1);
            count_r = subcount(root->right, level-1);
            return count_l + count_r;
            }
    };
    
#endif

template <class T>
io_status read_file(tree<T>*, const char*);
