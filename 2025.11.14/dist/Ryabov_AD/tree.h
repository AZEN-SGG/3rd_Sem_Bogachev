#include "tree_node.h"

class tree{
    private:
        tree_node * root = nullptr;
    public:
        tree () = default;
        tree (const tree& x) = delete;
        tree (tree&& x){
            root = x.root; x.root = nullptr;
        }
        ~tree (){
            delete_subtree (root);
            root = nullptr;
        }
        tree& operator= (const tree& x) = delete;
        tree& operator= (tree&& x){
            if (this == &x) return *this;
            delete_subtree (root);
            root = x.root; x.root = nullptr;
            return *this;
        }
        void print (unsigned int r = 10, FILE *fp = stdout) const{
            print_subtree (root, 0, r, fp);
        }
        io_status read (FILE * fp, unsigned int max_read);

        void task01();
        tree_node* poisk_max(tree_node* tek_root);
        void obhod01(tree_node* tek_root);

        void task02();
        int obhod_v_urovne(tree_node* tek_root, int ur, int tek_ur, int number, int& c, int& min, tree_node*& min_el, tree_node*& first_el);
        
        void task03();
        void prim03(tree_node*&parent, int is_lr, tree_node*&tek_root);
        tree_node* poisk_pred_left(tree_node* tek_root);

        void task04();
        void prim04(tree_node*&parent, int is_lr, tree_node*&tek_root);
        tree_node* poisk_pred_right(tree_node* tek_root);

        void task05(const student* sr);
        void solve05(tree_node* parent, int is_lr, tree_node* tek_root, const student* sr);
        int prov_ud05(tree_node* tek_root, const student* sr, int& flag);

        void task06(const student* sr);
        void solve06(tree_node* parent, int is_lr, tree_node* tek_root, const student* sr);
        int prov_ud06(tree_node* tek_root, const student* sr, int& flag);

        void task07(const student*sr);
        int solve07(const student* sr, int ur, int tek_ur, tree_node* tek_root, int& c, int& flag);
        void ud07(tree_node* tek_root, int ur, int tek_ur);

        int get_count_total() const;
        int get_count_total_rec(tree_node* tek_root) const;
        int get_count_leaf() const;
        int get_count_leaf_rec(tree_node* tek_root) const;
        int get_count_1() const;
        int get_count_1_rec(tree_node* tek_root) const;
        int get_count_2() const;
        int get_count_2_rec(tree_node* tek_root) const;
        int get_height() const;
        int get_height_rec(tree_node* tek_root) const;
        int get_width() const;
        int get_width_rec(tree_node* tek_root, int ur, int tek_ur) const;
        int get_balance() const;
        int get_balance_rec(int& max, tree_node* tek_root) const;
    private:
        static void delete_subtree (tree_node* curr){
            if (curr == nullptr) return;
            delete_subtree (curr->left);
            delete_subtree (curr->right);
            delete curr;
        }
        static void print_subtree (tree_node * curr, int level, int r, FILE *fp = stdout){
            if (curr == nullptr || level > r) return;
            int spaces = level * 2;
            for (int i = 0; i < spaces; i++) printf (" ");
            curr -> print(fp);
            print_subtree(curr->left, level + 1, r, fp);
            print_subtree(curr->right, level + 1, r, fp);
}
        static void add_node_subtree(tree_node * curr, tree_node *x);
};