#include "tree.h"

void tree::add_node_subtree(tree_node *curr, tree_node *x){
    if (*x < *curr){
        if (curr -> left == nullptr) curr -> left = x;
        else add_node_subtree(curr -> left, x);
    }
    else {
        if (curr -> right == nullptr) curr -> right = x;
        else add_node_subtree(curr -> right, x);
    }
}

io_status tree::read(FILE*fp, unsigned int max_read = -1){
    tree_node x;
    unsigned int c = 0;
    while (c < max_read && x.read(fp) == io_status::success){
        c++;
        tree_node *curr = new tree_node((tree_node&&)x);
        if (curr == nullptr){
            delete_subtree(root);
            return io_status::memory;
        }
        if (root == nullptr){
            root = curr;
        }
        else{
            add_node_subtree(root, curr);
        }
    }
    if (!feof(fp) && c < max_read){
        delete_subtree(root);
        return io_status::format;
    }
    return io_status::success;
}

int tree::get_count_total() const{
    if (!root) return 0;
    return get_count_total_rec(root);
}

int tree::get_count_total_rec(tree_node* tek_root) const{
    int c = 1;
    if (tek_root -> left){
        c += get_count_total_rec(tek_root -> left);
    }
    if (tek_root -> right){
        c += get_count_total_rec(tek_root -> right);
    }
    return c;
}

int tree::get_count_leaf() const {
    if (!root) return 0;
    return get_count_leaf_rec(root);
}

int tree::get_count_leaf_rec(tree_node* tek_root) const {
    int c = 0;
    if (tek_root -> right && tek_root -> left){
        c += get_count_leaf_rec(tek_root -> right);
        c += get_count_leaf_rec(tek_root -> left);
    }
    else if (tek_root -> right){
        c += get_count_leaf_rec(tek_root -> right);
    }
    else if (tek_root -> left){
        c += get_count_leaf_rec(tek_root -> left);
    }
    else {
        c += 1;
    }
    return c;
}

int tree::get_count_1() const{
    if (!root) return 0;
    return get_count_1_rec(root);
}
int tree::get_count_1_rec(tree_node* tek_root) const{
    int c = 0;
    if (tek_root -> left && tek_root -> right){
        c += get_count_1_rec(tek_root -> left);
        c += get_count_1_rec(tek_root -> right);
    }
    else if (tek_root -> right){
        c += 1;
        c += get_count_1_rec(tek_root -> right);
    }
    else if (tek_root -> left){
        c += 1;
        c += get_count_1_rec(tek_root -> left);
    }
    return c;
}

int tree::get_count_2() const{
    if (!root) return 0;
    return get_count_2_rec(root);
}
int tree::get_count_2_rec(tree_node* tek_root) const{
    int c = 0;
    if (tek_root -> left && tek_root -> right){
        c += 1;
        c += get_count_2_rec(tek_root -> left);
        c += get_count_2_rec(tek_root -> right);
    }
    else if (tek_root -> right){
        c += get_count_2_rec(tek_root -> right);
    }
    else if (tek_root -> left){
        c += get_count_2_rec(tek_root -> left);
    }
    return c;
}

int tree::get_height() const{
    if (!root) return 0;
    return get_height_rec(root);
}

int tree::get_height_rec(tree_node* tek_root) const{
    int max = 0;
    int c = 0;
    if (tek_root -> left && tek_root -> right){
        max = get_height_rec(tek_root -> left);
        c = get_height_rec(tek_root -> right);
        if (c > max){
            max = c;
        }
    }
    else if (tek_root -> right){
        max = get_height_rec(tek_root -> right); 
    }
    else if (tek_root -> left){
        max = get_height_rec(tek_root -> left);
    }
    return max + 1;
}

int tree::get_width() const{
    if (!root) return 0;
    int ur = 0;
    int max;
    int kol = get_width_rec(root, ur, 0); 
    max = kol;
    while (kol){
        ur += 1;
        kol = get_width_rec(root, ur, 0);
        if (kol > max){
            max = kol;
        }
    }
    return max;
}

int tree::get_width_rec(tree_node* tek_root, int ur, int tek_ur) const{
    int c = 0;
    if (tek_ur == ur){
        return 1;
    }
    if (tek_root -> left){
        c += get_width_rec(tek_root -> left, ur, tek_ur + 1);
    }
    if (tek_root -> right){
        c += get_width_rec(tek_root -> right, ur, tek_ur + 1);
    }
    return c;
}

int tree::get_balance() const{
    if (!root) return 0;
    int max = 0;
    get_balance_rec(max, root);
    return max; 
}

int tree::get_balance_rec(int& max, tree_node* tek_root) const{
    int glub_left = 0;
    int glub_right = 0;
    int c = 0;
    if (tek_root -> left){
        glub_left = get_balance_rec(max, tek_root -> left) + 1;
    }
    else{
        glub_left = 1;
    }
    if (tek_root -> right){
        glub_right = get_balance_rec(max, tek_root -> right) + 1;
    }
    else{
        glub_right = 1;
    }
    // ищем абсолютное значение
    c = glub_left - glub_right;
    if (c < 0){
        c *= -1;
    }
    if (c > max){
        max = c;
    }
    // ищем глубину
    if (glub_left >= glub_right){
        c = glub_left;
    }
    else{
        c = glub_right;
    }
    //
    return c;
}