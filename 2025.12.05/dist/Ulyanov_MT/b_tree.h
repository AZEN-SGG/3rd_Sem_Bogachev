#include "io_status.h"
#ifndef b_tree_H
#define b_tree_H
#include <stdio.h>
#include <string.h>

template <class T> class b_tree_node;
template <class T> class b_tree;

template <class T>
class b_tree_node
    {
    private:
        T* values = nullptr;
        int size = 0;
        b_tree_node** children = nullptr;
    public:
        b_tree_node() = default;
        b_tree_node(const b_tree_node& x) = delete;
        b_tree_node(b_tree_node&& x)
            {
            values = x.values;
            children = x.children;
            size = x.size;
            
            x.erase_links();
            }
        b_tree_node& operator= (const b_tree_node& x) = delete;
        b_tree_node& operator= (b_tree_node&& x)
            {
            if (this == &x) return *this;
            
            delete_node();
            
            values = x.values;
            children = x.children;
            size = x.size;
            
            x.erase_links();
            return *this;
            }
        ~b_tree_node() {delete_node();}
        
        void print(int p = 0, FILE* fp = stdout)
            {
            for (int i = 0; i < size; ++i)
                {
                for (int j = 0; j < p; j++) fprintf(fp, " ");
                fprintf(fp, "values[%2d] ", i+1);
                values[i].print(fp);
                }
            }
        int bin_search(const T& x) const
            {
            int l = 0, r = size, m;
            while (l != r) 
                {
                m = (l + r) / 2;
                if (values[m] < x) l = m + 1;
                else r = m;
                }
            return l;
            }
        
        friend class b_tree<T>;
        
    private:
        void erase_links()
            {
            values = nullptr;
            children = nullptr;
            size = 0;
            }
        void delete_node()
            {
            if (values != nullptr) delete [] values;
            if (children != nullptr) delete [] children;
            erase_links();
            }
            
        io_status init(int m)
            {
            values = new T[2 * m];
            if (values == nullptr) return io_status::memory;
            children = new b_tree_node*[2 * m + 1];
            if (children == nullptr)
                {
                delete [] values;
                values = nullptr;
                return io_status::memory;
                }
            for (int i = 0; i < 2 * m + 1; ++i) children[i] = nullptr;
            size = 0;
            return io_status::success;
            }
        void add_value(T& x, b_tree_node<T>* down, int index)
            {
            for (int i = size; i > index; i--)
                {
                values[i] = static_cast<T&&>(values[i-1]);
                children[i+1] = children[i];
                }
            values[index] = static_cast<T&&>(x);
            children[index+1] = down;
            size++;
            }
    };
    
template <class T>
class b_tree
    {
    private:
        int m = 0;
        b_tree_node<T>* root = nullptr;
    public:
        b_tree(int i = 0) {m = i;}
        b_tree(const b_tree& x) = delete;
        
        b_tree& operator= (const b_tree& x) = delete;
        
        ~b_tree()
            {
            delete_subtree(root);
            erase_links();
            }
        
        io_status read(FILE* fp = stdin)
            {
            T x;
            while (x.read(fp) == io_status::success) add_value(x);
            if (!feof(fp))
                {
                delete_subtree(root);
                return io_status::format;
                }
            return io_status::success;
            }
            
        void print(int r, FILE* fp = stdout) const {print_subtree(root, 0, r, fp);}
        
        int solve1(int k)
            {
            int amount = 0, count = 0;
            b_tree subtree;
            if (!root) return 0;
            if (!(root->children[0])) {if (k == 0) return root->size; else return 0;}
            for (int i = 0; i <= root->size; i++)
                {
                if (root->children[i]) {subtree.root = root->children[i]; amount++;}
                else break;
                count += subtree.solve1(k);
                }
            if (amount == k) count += root->size;
            
            subtree.root = nullptr;
            return count;
            }
        int solve2(int k, int* ret = nullptr)
            {
            int amount = 0, count = 0, len = 0;
            b_tree subtree;
            
            if (k <= 0) return 0;
            if (!root) {if (ret) *ret = 0; return 0;}
            if (!(root->children[0])) {if (ret) *ret = 1; return root->size;}
            for (int i = 0; i <= root->size; i++)
                {
                if (root->children[i])
                    {
                    subtree.root = root->children[i]; 
                    count += subtree.solve2(k, &len);
                    amount += len;
                    }
                else break;
                }
            amount++;
            if (amount <= k) count += root->size;
            if (ret) *ret = amount;
            
            subtree.root = nullptr;
            return count;
            }
        int solve3(int k, int* ret = nullptr)
            {
            int count = 0, maxlen = 0;
            b_tree subtree;
            
            if (k <= 0) return 0;
            if (!root) {if (ret) *ret = 0; return 0;}
            if (!(root->children[0])) {if (ret) *ret = 1; return root->size;}
            for (int i = 0; i <= root->size; i++)
                {
                if (root->children[i])
                    {
                    subtree.root = root->children[i];
                    count += subtree.solve3(k, &maxlen);
                    }
                else break;
                }            
            if (maxlen < k) count += root->size;
            if (ret) *ret = maxlen + 1;
            subtree.root = nullptr;
            return count;
            }
        int solve4(int k, int* ret = nullptr)
            {
            int count = 0, amount = 0, len = 0;
            b_tree subtree;
            
            if (k <= 0) return 0;
            if (!root) {if (ret) *ret = 0; return 0;}
            if (!(root->children[0])) {if (ret) *ret = 1; return root->size;}
            
            for (int i = 0; i <= root->size; i++)
                {
                if (root->children[i])
                    {
                    subtree.root = root->children[i];
                    count += subtree.solve4(k, &len);
                    amount += len;
                    }
                else break;
                }
                
            if (amount <= k) count += root->size;
            if (ret) *ret = amount;
            subtree.root = nullptr;
            return count;
            }
        int solve5(int k)
            {
            int count = 0;
            count = count_k_level(root, k);
            return count;
            }
        int solve6(int k, int* ret = nullptr)
            {
            int count = 0, len = 0;
            b_tree subtree;
            
            if (k <= 0) return 0;
            if (!root) {if (ret) *ret = 0; return 0;}
            if (!(root->children[0]))
                {
                if (ret) {*ret = 1; return root->size;}
                else if (k == 1) return root->size;
                else return 0;
                }
            
            for (int i = 0; i <= root->size; i++)
                {
                if (root->children[i]) 
                    {
                    subtree.root = root->children[i];
                    count += subtree.solve6(k, &len);
                    }
                else break;
                }
            
            count += root->size;
            if (ret) *ret = len + 1;
            else if (len + 1 != k) count = 0;
            subtree.root = nullptr;
            return count;
            }
    private:
        void erase_links()
            {
            m = 0;
            root = nullptr;
            }
        static void delete_subtree(b_tree_node<T>* curr)
            {
            if (curr == nullptr) return;
            for (int i = 0; i <= curr->size; i++) delete_subtree(curr->children[i]);
            delete curr;
            }
        static void print_subtree(b_tree_node<T>* curr, int level, int r, FILE* fp = stdout)
            {
            if (curr == nullptr || level > r) return;
            curr->print(level, fp);
            for (int i = 0; i <= curr->size; i++)
                {
                if (curr->children[i] && level + 1 <= r)
                    {
                    for (int j = 0; j < level; j++) fprintf(fp, " ");
                    fprintf(fp, "children[%2d]\n", i);
                    print_subtree(curr->children[i], level + 1, r, fp);
                    }
                }
            }
        
        io_status add_value(T& x)
            {
            if (root == nullptr)
                {
                root = new b_tree_node<T>();
                if (root == nullptr) return io_status::memory;
                if (root->init(m) != io_status::success) {delete root; return io_status::memory;} 
                root->values[0] = static_cast<T&&>(x);
                root->size = 1;
                return io_status::success;
                }
            
            b_tree_node<T>* curr = root;
            b_tree_node<T>* down = nullptr;
            io_status r = add_value_subtree(curr, down, x, m);
            
            if (r == io_status::memory) return io_status::memory;
            if (r == io_status::success) return io_status::success;
            
            b_tree_node<T>* p = new b_tree_node<T>();
            if (p == nullptr) return io_status::memory;
            if (p->init(m) != io_status::success) {delete p; return io_status::memory;}
            
            p->values[0] = static_cast<T&&>(x);
            p->children[0] = curr;
            p->children[1] = down;
            p->size = 1;
            
            root = p;
            
            return io_status::success;
            }
        static io_status add_value_subtree(b_tree_node<T>*& curr, b_tree_node<T>*& down, T& x, int m)
            {
            int index = curr->bin_search(x);
            b_tree_node<T>* p = curr->children[index];
            if (p != nullptr)
                {
                io_status r = add_value_subtree(p, down, x, m);
                if (r == io_status::memory) return io_status::memory;
                if (r == io_status::success) return io_status::success;
                }
            else down = nullptr;
            
            if (curr->size < 2 * m) {curr->add_value(x, down, index); return io_status::success;}
            else
                {
                b_tree_node<T>* p = new b_tree_node<T>();
                if (p == nullptr) return io_status::memory;
                if (p->init(m) != io_status::success) {delete p; return io_status::memory;}
                if (index == m)
                    {
                    for (int i = 1; i <= m; i++)
                        {
                        p->values[i-1] = static_cast<T&&>(curr->values[i + m - 1]);
                        p->children[i] = curr->children[i + m];
                        curr->children[i + m] = nullptr;
                        }
                    p->children[0] = down;
                    }
                if (index < m)
                    {
                    for (int i = 0; i < m; i++)
                        {
                        p->values[i] = static_cast<T&&>(curr->values[i + m]);
                        p->children[i] = curr->children[i + m];
                        curr->children[i + m] = nullptr;
                        }
                    p->children[m] = curr->children[2 * m];
                    curr->children[2 * m] = nullptr;
                    for (int i = m; i > index; i--)
                        {
                        curr->values[i] = static_cast<T&&>(curr->values[i-1]);
                        curr->children[i+1] = curr->children[i];
                        }
                    curr->children[index + 1] = down;
                    curr->values[index] = static_cast<T&&>(x);
                    x = static_cast<T&&>(curr->values[m]);
                    }
                if (index > m)
                    {
                    p->children[0] = curr->children[m+1];
                    curr->children[m+1] = nullptr;
                    for (int i = 1; i < index - m; i++)
                        {
                        p->values[i-1] = static_cast<T&&>(curr->values[i + m]);
                        p->children[i] = curr->children[i + m + 1];
                        curr->children[i + m + 1] = nullptr;
                        }
                    p->values[index - m - 1] = static_cast<T&&>(x);
                    p->children[index - m] = down;
                    for (int i = index - m + 1; i <= m; i++)
                        {
                        p->values[i - 1] = static_cast<T&&>(curr->values[i + m - 1]);
                        p->children[i] = curr->children[i + m];
                        curr->children[i + m] = nullptr;
                        }
                    x = static_cast<T&&>(curr->values[m]);
                    }
                down = p;
                p->size = m;
                curr->size = m;
                return io_status::create;
                }
            return io_status::success;
            }
        static int count_k_level(b_tree_node<T>* curr, int k)
            {
            int count = 0;
            if (!curr) return 0;
            if (k == 0) return curr->size;
            for (int i = 0; i <= curr->size; i++)
                {
                if (curr->children[i])
                    count += count_k_level(curr->children[i], k - 1);
                else break;
                }
            return count;
            }
    };
    
#endif

template <class T>
io_status read_file(b_tree<T>*, const char*);
