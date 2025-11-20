#include "student.h"

void student::print(FILE *fp) const { fprintf(fp, "%s %d\n", name, value); }

io_status student::read(FILE *fp) {
    const int LEN = 1234;
    char n[LEN];
    int v;
    if (fscanf(fp, "%s%d", n, &v) != 2) {
        if (!feof(fp)) return io_status::format;
        return io_status::eof;
    }
    erase();
    return init(n, v);
}

io_status student::init(const char *n, int v) {
    value = v;
    if (n != nullptr) {
        size_t len = strlen(n);
        name = new char[len + 1];
        if (name != nullptr) {
            for (size_t i = 0; i <= len; i++) name[i] = n[i];
        } else
            return io_status::memory;
    } else
        name = nullptr;
    return io_status::success;
}
void student::erase() {
    value = 0;
    if (name != nullptr) {
        delete[] name;
        name = nullptr;
    }
}
int student::cmp(const student &x) const {
    if (name == nullptr) {
        if (x.name != nullptr) return -1;
        return value - x.value;
    }
    if (x.name == nullptr) return 1;
    int res = strcmp(name, x.name);
    if (res) return res;
    return value - x.value;
}

int tree::get_count_total() const { return count_total_subtree(root); }

int tree::count_total_subtree(tree_node *curr) {
    if (curr == nullptr) return 0;
    return 1 + count_total_subtree(curr->left) + count_total_subtree(curr->right);
}

int tree::get_count_leaf() const { return count_leaves_subtree(root); }

int tree::count_leaves_subtree(tree_node *curr) {
    if (curr == nullptr) return 0;
    if (curr->left == nullptr && curr->right == nullptr) return 1;
    return count_leaves_subtree(curr->left) + count_leaves_subtree(curr->right);
}

int tree::get_count_1() const { return count_1_subtree(root); }

int tree::count_1_subtree(tree_node *curr) {
    if (curr == nullptr) return 0;
    int count = 0;
    if ((curr->left == nullptr && curr->right != nullptr) ||
        (curr->left != nullptr && curr->right == nullptr))
        count = 1;
    return count + count_1_subtree(curr->left) + count_1_subtree(curr->right);
}

int tree::get_count_2() const { return count_2_subtree(root); }

int tree::count_2_subtree(tree_node *curr) {
    if (curr == nullptr) return 0;
    int count = 0;
    if (curr->left != nullptr && curr->right != nullptr) count = 1;
    return count + count_2_subtree(curr->left) + count_2_subtree(curr->right);
}

int tree::get_height() const { return max_branch_length_subtree(root); }

int tree::max_branch_length_subtree(tree_node *curr) {
    if (curr == nullptr) return 0;
    int left_height = max_branch_length_subtree(curr->left);
    int right_height = max_branch_length_subtree(curr->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

int tree::get_width() const {
    if (root == nullptr) return 0;

    int height = max_branch_length_subtree(root);
    int max_width = 0;

    for (int level = 1; level <= height; level++) {
        int width = get_level_width(root, level);
        if (width > max_width) max_width = width;
    }

    return max_width;
}

int tree::get_level_width(tree_node *curr, int level) {
    if (curr == nullptr) return 0;
    if (level == 1) return 1;
    return get_level_width(curr->left, level - 1) +
           get_level_width(curr->right, level - 1);
}

int tree::get_balance() const {
    int max_diff = 0;
    max_depth_difference_subtree(root, max_diff);
    return max_diff;
}

int tree::max_depth_difference_subtree(tree_node *curr, int &max_diff) {
    if (curr == nullptr) return 0;

    int left_depth = max_depth_difference_subtree(curr->left, max_diff);
    int right_depth = max_depth_difference_subtree(curr->right, max_diff);

    int diff = std::abs(left_depth - right_depth);
    if (diff > max_diff) max_diff = diff;

    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}

io_status tree::read(FILE *fp, unsigned int max_read) {
    unsigned int count = 0;
    io_status status;

    while (count < max_read) {
        tree_node *new_node = new tree_node();
        if (new_node == nullptr) return io_status::memory;

        status = new_node->read(fp);
        if (status == io_status::eof) {
            delete new_node;
            break;
        }
        if (status != io_status::success) {
            delete new_node;
            return status;
        }

        if (root == nullptr) {
            root = new_node;
        } else {
            add_node_subtree(root, new_node);
        }
        count++;
    }

    return io_status::success;
}

void tree::add_node_subtree(tree_node *curr, tree_node *x) {
    if (*x < *curr) {
        if (curr->left == nullptr)
            curr->left = x;
        else
            add_node_subtree(curr->left, x);
    } else {
        if (curr->right == nullptr)
            curr->right = x;
        else
            add_node_subtree(curr->right, x);
    }
}

void tree::task7(const student& stud) {
    const char* s = stud.get_name();
    int k = stud.get_value();
    delete_subtrees_by_level_sequence(root, s, k, &root);
}

void tree::delete_subtrees_by_level_sequence(tree_node* curr, const char* s, int k, tree_node** root_ptr) {
    if (curr == nullptr) return;
    
    // Сначала рекурсивно обрабатываем левое и правое поддеревья
    delete_subtrees_by_level_sequence(curr->left, s, k, root_ptr);
    delete_subtrees_by_level_sequence(curr->right, s, k, root_ptr);
    
    // Проверяем условие для текущего поддерева: есть ли уровень с последовательностью >= k узлов, содержащих s
    if (has_level_sequence_condition(curr, s, k)) {
        // Сохраняем информацию о родителе ДО удаления
        tree_node* parent = nullptr;
        bool is_left_child = false;
        
        if (*root_ptr != curr) {
            parent = find_parent(*root_ptr, curr);
            if (parent != nullptr) {
                is_left_child = (parent->left == curr);
            }
        }
        
        // Удаляем все поддерево с корнем в curr
        delete_subtree(curr);
        
        // Обновляем ссылку у родителя (если есть)
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

bool tree::has_level_sequence_condition(tree_node* curr, const char* s, int k) {
    if (curr == nullptr) return false;
    
    int height = get_tree_height(curr);
    
    // Проверяем каждый уровень поддерева
    for (int level = 0; level < height; level++) {
        // Получаем узлы текущего уровня
        int count = get_level_count(curr, level);
        if (count > 0) {
            tree_node** level_nodes = new tree_node*[count];
            int index = 0;
            collect_level_nodes(curr, level_nodes, level, index);
            
            // Проверяем есть ли последовательность >= k узлов, содержащих s
            if (has_consecutive_nodes_with_s(level_nodes, count, s, k)) {
                delete[] level_nodes;
                return true;
            }
            
            delete[] level_nodes;
        }
    }
    
    return false;
}

bool tree::has_consecutive_nodes_with_s(tree_node** nodes, int count, const char* s, int k) {
    if (k <= 0) return true;
    if (count < k) return false;
    
    int current_streak = 0;
    
    for (int i = 0; i < count; i++) {
        const char* node_name = nodes[i]->get_name();
        if (node_name != nullptr && strstr(node_name, s) != nullptr) {
            current_streak++;
            if (current_streak >= k) {
                return true;
            }
        } else {
            current_streak = 0;
        }
    }
    
    return false;
}
