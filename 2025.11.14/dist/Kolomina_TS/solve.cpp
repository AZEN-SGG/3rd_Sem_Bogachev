#include "student.h"

void tree::task1() {
    transform_to_max_subtree(root);
}

void tree::transform_to_max_subtree(tree_node* curr) {
    if (curr == nullptr) return;
    
    tree_node* max_node = find_max_in_subtree(curr);
    
    if (max_node != curr && max_node != nullptr) {
        swap_nodes_data(curr, max_node);
    }
    
    transform_to_max_subtree(curr->left);
    transform_to_max_subtree(curr->right);
}

tree_node* tree::find_max_in_subtree(tree_node* curr) {
    if (curr == nullptr) return nullptr;
    
    tree_node* max_node = curr;

    tree_node* left_max = find_max_in_subtree(curr->left);
    if (left_max != nullptr && *left_max > *max_node) {
        max_node = left_max;
    }

    tree_node* right_max = find_max_in_subtree(curr->right);
    if (right_max != nullptr && *right_max > *max_node) {
        max_node = right_max;
    }
    
    return max_node;
}

void tree::swap_nodes_data(tree_node* a, tree_node* b) {
    tree_node* left_a = a->left;
    tree_node* right_a = a->right;
    
    tree_node* left_b = b->left;
    tree_node* right_b = b->right;
    
    tree_node temp;
    temp = std::move(*a);
    
    *a = std::move(*b);
    
    *b = std::move(temp);

    a->left = left_a;
    a->right = right_a;
    b->left = left_b;
    b->right = right_b;
}

void tree::task2() {
    sort_level_by_value(root);
}

void tree::sort_level_by_value(tree_node* curr) {
    if (curr == nullptr) return;
    
    int height = get_tree_height(curr);
    
    for (int level = 0; level < height; level++) {
        int count = get_level_count(curr, level);
        
        if (count > 1) {
            tree_node** level_nodes = new tree_node*[count];
            int index = 0;
            
            collect_level_nodes(curr, level_nodes, level, index);
            
            sort_level_nodes(level_nodes, count);
            
            delete[] level_nodes;
        }
    }
}

int tree::get_tree_height(tree_node* curr) {
    if (curr == nullptr) return 0;
    int left_height = get_tree_height(curr->left);
    int right_height = get_tree_height(curr->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

int tree::get_level_count(tree_node* curr, int level) {
    if (curr == nullptr) return 0;
    if (level == 0) return 1;
    return get_level_count(curr->left, level - 1) + get_level_count(curr->right, level - 1);
}

void tree::collect_level_nodes(tree_node* curr, tree_node** nodes, int level, int& index) {
    if (curr == nullptr) return;
    if (level == 0) {
        nodes[index++] = curr;
        return;
    }
    collect_level_nodes(curr->left, nodes, level - 1, index);
    collect_level_nodes(curr->right, nodes, level - 1, index);
}

void tree::sort_level_nodes(tree_node** nodes, int count) {
    for (int i = 0; i < count - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < count; j++) {
            if (nodes[j]->get_value() < nodes[min_index]->get_value()) {
                min_index = j;
            }
        }
        
        if (min_index != i) {
            swap_nodes_data(nodes[i], nodes[min_index]);
        }
    }
}

void tree::task3() {
    transform_task3_subtree(root, nullptr, false, &root);
}

void tree::transform_task3_subtree(tree_node* curr, tree_node* parent, bool is_left, tree_node** root_ptr) {
    if (curr == nullptr) return;
    
    transform_task3_subtree(curr->left, curr, true, root_ptr);
    transform_task3_subtree(curr->right, curr, false, root_ptr);
    
    if (curr->left == nullptr && curr->right != nullptr && !is_leaf(curr->right)) {
        tree_node* A = curr;
        tree_node* B = curr->right;
        
        tree_node* C = find_leftmost_leaf(B);
        
        if (C != nullptr && C != B) {
            tree_node* parent_C = find_parent(B, C);
            
            if (parent_C != nullptr) {
                if (parent_C->left == C) {
                    parent_C->left = nullptr;
                } else if (parent_C->right == C) {
                    parent_C->right = nullptr;
                }
            }
            
            tree_node* C_left = C->left;
            tree_node* C_right = C->right;
            
            if (parent != nullptr) {
                if (is_left) {
                    parent->left = C;
                } else {
                    parent->right = C;
                }
            } else {
                *root_ptr = C;
            }
            
            C->left = A;
            C->right = B;
            
            A->left = nullptr;
            A->right = nullptr;
            
            if (C_left != nullptr || C_right != nullptr) {
                if (parent_C != nullptr) {
                    if (parent_C->left == nullptr) {
                        parent_C->left = C_left;
                    } else if (parent_C->right == nullptr) {
                        parent_C->right = C_right;
                    }
                }
            }
        }
    }
}

tree_node* tree::find_leftmost_leaf(tree_node* curr) {
    if (curr == nullptr) return nullptr;
    
    if (curr->left != nullptr) {
        tree_node* left_result = find_leftmost_leaf(curr->left);
        if (left_result != nullptr) return left_result;
    }
    
    if (is_leaf(curr)) return curr;
    
    if (curr->right != nullptr) {
        return find_leftmost_leaf(curr->right);
    }
    
    return nullptr;
}

bool tree::is_leaf(tree_node* node) {
    return node != nullptr && node->left == nullptr && node->right == nullptr;
}

tree_node* tree::find_parent(tree_node* root, tree_node* target) {
    if (root == nullptr || target == nullptr || root == target) {
        return nullptr;
    }
    
    if (root->left == target || root->right == target) {
        return root;
    }
    
    tree_node* left_result = find_parent(root->left, target);
    if (left_result != nullptr) {
        return left_result;
    }
    
    return find_parent(root->right, target);
}

void tree::task4() {
    transform_task4_subtree(root, nullptr, false, &root);
}

void tree::transform_task4_subtree(tree_node* curr, tree_node* parent, bool is_left, tree_node** root_ptr) {
    if (curr == nullptr) return;
    
    transform_task4_subtree(curr->left, curr, true, root_ptr);
    transform_task4_subtree(curr->right, curr, false, root_ptr);
    
    if (curr->right == nullptr && curr->left != nullptr && !is_leaf(curr->left)) {
        tree_node* A = curr;
        tree_node* B = curr->left;
        
        tree_node* C = find_rightmost_leaf(B);
        
        if (C != nullptr && C != B) {
            tree_node* parent_C = find_parent(B, C);
            
            if (parent_C != nullptr) {
                if (parent_C->left == C) {
                    parent_C->left = nullptr;
                } else if (parent_C->right == C) {
                    parent_C->right = nullptr;
                }
            }
            
            tree_node* C_left = C->left;
            tree_node* C_right = C->right;
            
            if (parent != nullptr) {
                if (is_left) {
                    parent->left = C;
                } else {
                    parent->right = C;
                }
            } else {
                *root_ptr = C;
            }
            
            C->left = B;
            C->right = A;
            
            A->left = nullptr;
            A->right = nullptr;
            
            if (C_left != nullptr || C_right != nullptr) {
                if (parent_C != nullptr) {
                    if (parent_C->left == nullptr) {
                        parent_C->left = C_left;
                    } else if (parent_C->right == nullptr) {
                        parent_C->right = C_right;
                    }
                }
            }
        }
    }
}

tree_node* tree::find_rightmost_leaf(tree_node* curr) {
    if (curr == nullptr) return nullptr;
    
    if (curr->right != nullptr) {
        tree_node* right_result = find_rightmost_leaf(curr->right);
        if (right_result != nullptr) return right_result;
    }
    
    if (is_leaf(curr)) return curr;
    
    if (curr->left != nullptr) {
        return find_rightmost_leaf(curr->left);
    }
    
    return nullptr;
}

void tree::task5(const student& stud) {
    const char* s = stud.get_name();
    int k = stud.get_value();
    delete_subtrees_by_condition(root, s, k, &root);
}

void tree::delete_subtrees_by_condition(tree_node* curr, const char* s, int k, tree_node** root_ptr) {
    if (curr == nullptr) return;
    
    delete_subtrees_by_condition(curr->left, s, k, root_ptr);
    delete_subtrees_by_condition(curr->right, s, k, root_ptr);
    
    if (should_delete_subtree(curr, s, k)) {
        tree_node* parent = nullptr;
        bool is_left_child = false;
        
        if (*root_ptr != curr) {
            parent = find_parent(*root_ptr, curr);
            if (parent != nullptr) {
                is_left_child = (parent->left == curr);
            }
        }
        
        delete_subtree(curr);
        
        if (*root_ptr == curr) {
            *root_ptr = nullptr;
        } else if (parent != nullptr) {
            if (is_left_child) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
    }
}

bool tree::should_delete_subtree(tree_node* curr, const char* s, int k) {
    return (get_subtree_depth(curr) >= k) && (all_nodes_contain_string(curr, s));
}

int tree::get_subtree_depth(tree_node* curr) {
    if (curr == nullptr) return 0;
    
    int left_depth = get_subtree_depth(curr->left);
    int right_depth = get_subtree_depth(curr->right);
    
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}

bool tree::all_nodes_contain_string(tree_node* curr, const char* s) {
    if (curr == nullptr) return true;
    
    const char* node_name = curr->get_name();
    if (node_name == nullptr || strstr(node_name, s) == nullptr) {
        return false;
    }
    
    return all_nodes_contain_string(curr->left, s) && 
           all_nodes_contain_string(curr->right, s);
}

void tree::task6(const student& stud) {
    const char* s = stud.get_name();
    int k = stud.get_value();
    delete_subtrees_with_branch_condition(root, s, k, &root);
}

void tree::delete_subtrees_with_branch_condition(tree_node* curr, const char* s, int k, tree_node** root_ptr) {
    if (curr == nullptr) return;
    
    delete_subtrees_with_branch_condition(curr->left, s, k, root_ptr);
    delete_subtrees_with_branch_condition(curr->right, s, k, root_ptr);
    
    if (has_branch_with_condition(curr, s, k)) {
        tree_node* parent = nullptr;
        bool is_left_child = false;
        
        if (*root_ptr != curr) {
            parent = find_parent(*root_ptr, curr);
            if (parent != nullptr) {
                is_left_child = (parent->left == curr);
            }
        }
        
        delete_subtree(curr);
        
        if (*root_ptr == curr) {
            *root_ptr = nullptr;
        } else if (parent != nullptr) {
            if (is_left_child) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
    }
}

bool tree::has_branch_with_condition(tree_node* curr, const char* s, int k) {
    if (curr == nullptr) return false;
    
    return check_branch_condition(curr, s, k, 1);
}

bool tree::check_branch_condition(tree_node* curr, const char* s, int k, int current_length) {
    if (curr == nullptr) return false;
    
    const char* node_name = curr->get_name();
    if (node_name == nullptr || strstr(node_name, s) == nullptr) {
        return false;
    }
    
    if (current_length >= k) {
        return true;
    }
    
    if (check_branch_condition(curr->left, s, k, current_length + 1)) {
        return true;
    }
    
    if (check_branch_condition(curr->right, s, k, current_length + 1)) {
        return true;
    }
    
    return false;
}