#include <string.h>
#include "tree.h"

void tree::task01(){
    obhod01(root);
    return;
}

tree_node* tree::poisk_max(tree_node* tek_root){
    tree_node*left_max;
    tree_node*right_max;
    if (tek_root -> left && tek_root -> right){
        left_max = poisk_max(tek_root -> left);
        right_max = poisk_max(tek_root -> right);
        if (*left_max > *right_max){
            if (*left_max > *tek_root){
                return left_max;   
            }
        }
        else{
            if (*right_max > *tek_root){
                return right_max;
            }
        }
        return tek_root;
    }
    else if (tek_root -> left){
        left_max = poisk_max(tek_root -> left);
        if (*left_max > *tek_root){
            return left_max;   
        }
        return tek_root;
    }
    else if (tek_root -> right){
        right_max = poisk_max(tek_root -> right);
        if (*right_max > *tek_root){
            return right_max;
        }
        return tek_root;
    }
    else{
        return tek_root;
    }
}
void tree::obhod01(tree_node* tek_root){
    tree_node* max;
    char* swap_str;
    int swap_value;
    max = poisk_max(tek_root);
    if (max && *max > *tek_root){
        swap_str = tek_root -> name;
        swap_value = tek_root -> value;
        tek_root -> name = max -> name;
        tek_root -> value = max -> value;
        max -> name = swap_str;
        max -> value = swap_value;
    }
    if (tek_root -> left){
        obhod01(tek_root -> left);
    }
    if (tek_root -> right){
        obhod01(tek_root -> right);
    }
    return;
}

void tree::task02(){
    int ur = 0;
    int number = 1;
    while (number != 0){
        int tek_ur = 0;
        number = 0; // с какого элемента начинается поиск минимума
        int min = 2147483647;
        int c = 0;
        tree_node* min_el = nullptr;
        tree_node* first_el = nullptr;
        char* swap_str = nullptr;
        int swap_value = 0;
        int kol = obhod_v_urovne(root, ur, tek_ur, number, c, min, min_el, first_el);
        (void)kol;
        while (c > number){ // т. е. пока не перерали весь список'
            if (min_el && first_el){
                swap_str = min_el -> name;
                swap_value = min_el -> value;
                min_el -> name = first_el -> name;
                min_el -> value = first_el -> value;
                first_el -> name = swap_str;
                first_el -> value = swap_value;
            }
            number += 1;
            min_el = nullptr;
            first_el = nullptr;
            c = 0;
            min = 2147483647;
            obhod_v_urovne(root, ur, tek_ur, number, c, min, min_el, first_el);
        }
        ur++;
    }
    return;
}

int tree::obhod_v_urovne(tree_node* tek_root, int ur, int tek_ur, int number, int& c, int& min, tree_node*& min_el, tree_node*& first_el){
    int ob_el = 0;
    if (tek_ur == ur){
        if (c == number){
            first_el = tek_root;
        }
        if (c >= number){
            if (tek_root -> value < min){
                min = tek_root -> value;
                min_el = tek_root;
            }
        }
        c += 1;
        return 1;
    }
    if (tek_root -> left){
        ob_el += obhod_v_urovne(tek_root -> left, ur, tek_ur + 1, number, c, min, min_el, first_el);
    }
    if (tek_root -> right){
        ob_el += obhod_v_urovne(tek_root -> right, ur, tek_ur + 1, number, c, min, min_el, first_el);
    }
    return ob_el;
}

void tree::task03(){
    tree_node*parent = nullptr;
    prim03(parent, 0, root);
}

void tree::prim03(tree_node*&parent, int is_lr, tree_node*&tek_root){ // is_lr = 1 - left = 2 - right
    tree_node* pred_left;
    tree_node* left_el;
    (void) is_lr;
    (void) parent;
    char* swap_str = nullptr;
    int swap_value = 0;
    if (!(tek_root -> left) && tek_root -> right && (tek_root -> right -> right || tek_root -> right -> left)){
        pred_left = poisk_pred_left(tek_root -> right);
        if (pred_left){
            left_el = pred_left -> left;
            if (!(left_el -> right)){
                //
                pred_left -> left = nullptr;
                tek_root -> left = left_el;
                swap_str = tek_root -> name;
                swap_value = tek_root -> value;
                tek_root -> name = left_el -> name;
                tek_root -> value = left_el -> value;
                left_el -> name = swap_str;
                left_el -> value = swap_value;
            }
        }
    }
    if (tek_root -> left){
        prim03(tek_root, 1, tek_root -> left);
    }
    if (tek_root -> right){
        prim03(tek_root, 2, tek_root -> right);
    }
}

tree_node* tree::poisk_pred_left(tree_node* tek_root){
    if (tek_root -> left){
        if (tek_root -> left -> left){
            return poisk_pred_left(tek_root -> left);
        }
        else{
            return tek_root;
        }
    }
    else{ // Может сработать, если изначально нет никакого левого
        return nullptr;
    }
    return nullptr; // по идее, никогда не достигнет
}

void tree::task04(){
    tree_node*parent = nullptr;
    prim04(parent, 0, root);
}

void tree::prim04(tree_node*&parent, int is_lr, tree_node*&tek_root){ // is_lr = 1 - left = 2 - right
    tree_node* pred_right;
    tree_node* right_el;
    (void) is_lr;
    (void) parent;
    char* swap_str = nullptr;
    int swap_value = 0;
    if (!(tek_root -> right) && tek_root -> left && (tek_root -> left -> left || tek_root -> left -> right)){
        pred_right = poisk_pred_right(tek_root -> left);
        if (pred_right){
            right_el = pred_right -> right;
            if (!(right_el -> left)){
                //
                pred_right -> right = nullptr;
                tek_root -> right = right_el;
                swap_str = tek_root -> name;
                swap_value = tek_root -> value;
                tek_root -> name = right_el -> name;
                tek_root -> value = right_el -> value;
                right_el -> name = swap_str;
                right_el -> value = swap_value;
            }
        }
    }
    if (tek_root -> left){
        prim04(tek_root, 1, tek_root -> left);
    }
    if (tek_root -> right){
        prim04(tek_root, 2, tek_root -> right);
    }
}

tree_node* tree::poisk_pred_right(tree_node* tek_root){
    if (tek_root -> right){
        if (tek_root -> right -> right){
            return poisk_pred_right(tek_root -> right);
        }
        else{
            return tek_root;
        }
    }
    else{ // Может сработать, если изначально нет никакого левого
        return nullptr;
    }
    return nullptr; // по идее, никогда не достигнет
}

void tree::task05(const student* sr){
    solve05(nullptr, 0, root, sr);
    return;
}

void tree::solve05(tree_node* parent, int is_lr, tree_node* tek_root, const student* sr){
    int flag = 1;
    int kol = prov_ud05(tek_root, sr, flag);
    if (kol >= sr -> value && flag){
        if (is_lr == 1){
            parent -> left = nullptr;
        }
        else if (is_lr == 2){
            parent -> right = nullptr;
        }
        delete_subtree(tek_root);
        if (is_lr == 0){
            root = nullptr;
        }
        return;
    }
    if (tek_root -> left){
        solve05(tek_root, 1, tek_root -> left, sr);
    }
    if (tek_root -> right){
        solve05(tek_root, 2, tek_root -> right, sr);
    }
}

int tree::prov_ud05(tree_node* tek_root, const student* sr, int& flag){
    int l1 = 0;
    int l2 = 0;
    if (!strstr(tek_root -> name, sr -> name)){
        flag = 0;
        return -1;
    }
    if (tek_root -> left){
        l1 = prov_ud05(tek_root -> left, sr, flag);
    }
    if (tek_root -> right){
        l2 = prov_ud05(tek_root -> right, sr, flag);
    }
    if (l1 > l2){
        return l1 + 1;
    }
    return l2 + 1;
}

void tree::task06(const student* sr){
    solve06(nullptr, 0, root, sr);
    return;
}

void tree::solve06(tree_node* parent, int is_lr, tree_node* tek_root, const student* sr){
    int flag = 1;
    int kol = prov_ud06(tek_root, sr, flag);
    if (kol >= sr -> value && flag){
        if (is_lr == 1){
            parent -> left = nullptr;
        }
        else if (is_lr == 2){
            parent -> right = nullptr;
        }
        delete_subtree(tek_root);
        if (is_lr == 0){
            root = nullptr;
        }
        return;
    }
    if (tek_root -> left){
        solve06(tek_root, 1, tek_root -> left, sr);
    }
    if (tek_root -> right){
        solve06(tek_root, 2, tek_root -> right, sr);
    }
}

int tree::prov_ud06(tree_node* tek_root, const student* sr, int& flag){
    int l1 = 0;
    int l2 = 0;
    int flag1 = 1;
    int flag2 = 1;
    if (!strstr(tek_root -> name, sr -> name)){
        flag = 0;
        return -1;
    }

    if (tek_root -> left){
        l1 = prov_ud06(tek_root -> left, sr, flag1);
    }
    if (tek_root -> right){
        l2 = prov_ud06(tek_root -> right, sr, flag2);
    }
    if (flag1 && flag2){
        if (l1 > l2){
            return l1 + 1;
        }
        return l2 + 1;
    }
    else if (flag1){
        return l1 + 1;
    }
    else if (flag2){
        return l2 + 1;
    }
    else{
        flag = 0;
        return -1;
    }
}

void tree::task07(const student* sr){
    int ur = 0;
    int c = 0;
    int max_c = 0;
    int is_prod = solve07(sr, ur, 0, root, c, max_c);
    if (c > max_c){
        max_c = c;
    }
    while (is_prod != 0){
        if (max_c >= sr -> value){
            if (ur == 0){
                delete_subtree(root);
                root = nullptr;
            }
            else{
                ud07(root, ur, 0);
            }
            return;
        }
        else{
            ur += 1;
            c = 0;
            max_c = 0;
            is_prod = solve07(sr, ur, 0, root, c, max_c);
            if (c > max_c){
                max_c = c;
            }
        }
    } 
    return;
}

void tree::ud07(tree_node* tek_root, int ur, int tek_ur){
    if (tek_ur + 1 == ur){
        if (tek_root -> left){
            delete_subtree(tek_root -> left);
            tek_root -> left = nullptr;
        }
        if (tek_root -> right){
            delete_subtree(tek_root -> right);
            tek_root -> right = nullptr;
        }
    }
    else{
        if (tek_root -> left){
            ud07(tek_root -> left, ur, tek_ur + 1);
        }
        if (tek_root -> right){
            ud07(tek_root -> right, ur, tek_ur + 1);
        }
    }
}

int tree::solve07(const student* sr, int ur, int tek_ur, tree_node* tek_root, int& c, int&max_c){
    int sum = 0;
    if (tek_ur == ur){
        if (!strstr(tek_root -> name, sr -> name)){
            if (c > max_c){
                max_c = c;
            }
            c = 0;
        }
        else{
            c += 1;
        }
        return 1;
    }
    if (tek_root -> left){
        sum += solve07(sr, ur, tek_ur + 1, tek_root -> left, c, max_c);
    }
    if (tek_root -> right){
        sum += solve07(sr, ur, tek_ur + 1, tek_root -> right, c, max_c);
    }
    return sum;
}