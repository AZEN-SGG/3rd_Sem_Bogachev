#ifndef STUDENT_H
#define STUDENT_H

#include <climits>
#include <cstdio>
#include <cstddef>
#include <cstring>
#include <stdlib.h>
#include <utility>

enum class io_status {
    success,
    eof,
    format,
    memory,
};

class student {
   private:
    char* name = nullptr;
    int value = 0;

   public:
    student() = default;
    student(const student& x) = delete;
    student(student&& x) {
        name = x.name;
        x.name = nullptr;
        value = x.value;
        x.value = 0;
    }
    student(const char *name, int value) {
        init(name, value);
    }
    ~student() { erase(); }
    student& operator=(const student& x) = delete;
    student& operator=(student&& x) {
        if (this == &x) return *this;
        erase();
        name = x.name;
        x.name = nullptr;
        value = x.value;
        x.value = 0;
        return *this;
    }
    void print(FILE* fp = stdout) const;
    io_status read(FILE* fp = stdin);

    int operator>(const student& x) const { return (cmp(x) > 0 ? 1 : 0); }
    int operator<(const student& x) const { return (cmp(x) < 0 ? 1 : 0); }
    int operator==(const student& x) const { return (cmp(x) == 0 ? 1 : 0); }
    int operator<=(const student& x) const { return (cmp(x) <= 0 ? 1 : 0); }
    int operator>=(const student& x) const { return (cmp(x) >= 0 ? 1 : 0); }

    int get_value() const { return value; }
    const char* get_name() const { return name; }

   private:
    io_status init(const char* n, int v);
    void erase();
    int cmp(const student& x) const;
};

class tree;

class tree_node : public student {
   private:
    tree_node* left = nullptr;
    tree_node* right = nullptr;

   public:
    tree_node() = default;
    tree_node(const tree_node& x) = delete;
    tree_node(tree_node&& x) : student((student&&)x) {
        erase_links();
        x.erase_links();
    }
    ~tree_node() { erase_links(); }
    tree_node& operator=(const tree_node& x) = delete;
    tree_node& operator=(tree_node&& x) {
        if (this == &x) return *this;
        (student&&)* this = (student&&)x;
        erase_links();
        x.erase_links();
        return *this;
    }
    friend class tree;

   private:
    void erase_links() {
        left = nullptr;
        right = nullptr;
    }
};

class tree {
   private:
    tree_node* root = nullptr;

   public:
    tree() = default;
    tree(const tree& x) = delete;
    tree(tree&& x) {
        root = x.root;
        x.root = nullptr;
    }
    ~tree() {
        delete_subtree(root);
        root = nullptr;
    }
    tree& operator=(const tree& x) = delete;
    tree& operator=(tree&& x) {
        if (this == &x) return *this;
        delete_subtree(root);
        root = x.root;
        x.root = nullptr;
        return *this;
    }
    void print(unsigned int r = 10, FILE* fp = stdout) const {
        print_subtree(root, 0, r, fp);
    }
    io_status read(FILE* fp = stdin, unsigned int max_read = -1);

    int get_count_total() const;
    int get_count_leaf() const;
    int get_count_1() const;
    int get_count_2() const;
    int get_height() const;
    int get_width() const;
    int get_balance() const;

    void task1();
    void task2();
    void task3();
    void task4();
    void task5(const student& stud);
    void task6(const student& stud);
    void task7(const student& stud);

   private:
    static void delete_subtree(tree_node* curr) {
        if (curr == nullptr) return;
        delete_subtree(curr->left);
        delete_subtree(curr->right);
        delete curr;
    }
    static void print_subtree(tree_node* curr, int level, int r,
                              FILE* fp = stdout) {
        if (curr == nullptr || level > r) return;
        int spaces = level * 2;
        for (int i = 0; i < spaces; i++) printf(" ");
        curr->print(fp);
        print_subtree(curr->left, level + 1, r, fp);
        print_subtree(curr->right, level + 1, r, fp);
    }
    static void add_node_subtree(tree_node* curr, tree_node* x);

    static int count_total_subtree(tree_node *curr);
    static int count_leaves_subtree(tree_node * curr);
    static int count_1_subtree(tree_node *curr);
    static int count_2_subtree(tree_node *curr);
    static int max_branch_length_subtree(tree_node * curr);
    static int get_level_width(tree_node * curr, int level);
    static int max_depth_difference_subtree(tree_node * curr, int &max_diff);

    static void transform_to_max_subtree(tree_node* curr);
    static tree_node* find_max_in_subtree(tree_node* curr);
    static void swap_nodes_data(tree_node* a, tree_node* b);

    static void sort_level_by_value(tree_node* curr);
    static int get_tree_height(tree_node* curr);
    static int get_level_count(tree_node* curr, int level);
    static void collect_level_nodes(tree_node* curr, tree_node** nodes, int level, int& index);
    static void sort_level_nodes(tree_node** nodes, int count);

    static void transform_task3_subtree(tree_node* curr, tree_node* parent, bool is_left, tree_node** root_ptr);
    static tree_node* find_leftmost_leaf(tree_node* curr);
    static bool is_leaf(tree_node* node);
    static tree_node* find_parent(tree_node* root, tree_node* target);

    static void transform_task4_subtree(tree_node* curr, tree_node* parent, bool is_left, tree_node** root_ptr);
    static tree_node* find_rightmost_leaf(tree_node* curr);

    static void delete_subtrees_by_condition(tree_node* curr, const char* s, int k, tree_node** root_ptr);
    static bool should_delete_subtree(tree_node* curr, const char* s, int k);
    static int get_subtree_depth(tree_node* curr);
    static bool all_nodes_contain_string(tree_node* curr, const char* s);

    static void delete_subtrees_with_branch_condition(tree_node* curr, const char* s, int k, tree_node** root_ptr);
    static bool has_branch_with_condition(tree_node* curr, const char* s, int k);
    static bool check_branch_condition(tree_node* curr, const char* s, int k, int current_length);

    static void delete_subtrees_by_level_sequence(tree_node* curr, const char* s, int k, tree_node** root_ptr);
    static bool has_level_sequence_condition(tree_node* curr, const char* s, int k);
    static bool has_consecutive_nodes_with_s(tree_node** nodes, int count, const char* s, int k);
};

#endif  // STUDENT_H