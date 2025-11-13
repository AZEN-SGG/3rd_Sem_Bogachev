#include "tree.h"

int tree::get_count_total_subtree (tree_node *curr)
{
	int count = 0;
	
	for (; (curr != nullptr) ; curr = curr->right, count++)
		count += get_count_total_subtree(curr->left);

	return count;
}

int tree::get_count_leaf () const
{
    int count = 0,
        is_end = 0;

    tree_node* curr = nullptr;
    for (curr = root ; (curr != nullptr) ; curr = curr->right)
    {
        is_end = 0;

        tree_node *left = curr->left;
        if (left != nullptr)
        {
            tree temp;
            temp.root = left;
            count += temp.get_count_leaf();
            temp.root = nullptr;
        } else
            is_end++;
    }

    count += is_end;

    return count;
}

int tree::get_count_1 () const
{
    int count = 0;
    
    tree_node *curr = nullptr,
              *child = nullptr;
    for (curr = root ; (curr != nullptr) ; curr = child)
    {
        tree_node *right = curr->right;

        child = curr->left;
        if ((child != nullptr) && (right != nullptr))
        {
            tree tmp;
            tmp.root = child;
            count += tmp.get_count_1();
            tmp.root = nullptr;

            child = right;
        } else if (child != nullptr)
            count++;
        else if (right != nullptr)
        {
            count++;
            child = right;
        }
    }

    return count;
}

int tree::get_count_2 () const
{
    int count = 0;
    
    tree_node *curr = nullptr,
              *child = nullptr;
    for (curr = root ; (curr != nullptr) ; curr = child)
    {
        tree_node *right = curr->right;

        child = curr->left;
        if ((child != nullptr) && (right != nullptr))
        {
            count++;

            tree tmp;
            tmp.root = child;
            count += tmp.get_count_2();
            tmp.root = nullptr;

            child = right;
	} else if (right != nullptr)
            child = right;
    }

    return count;
}

int tree::get_height () const
{
    int max_len = 0,
        len = 0;

    tree_node* curr = nullptr;
    for (curr = root ; (curr != nullptr) ; curr = curr->right)
    {
        len++;

        tree_node *left = curr->left;
        if (left != nullptr)
        {
            tree temp;
            temp.root = left;
            int temp_len = len + temp.get_height();
            temp.root = nullptr;

            max_len = (max_len < temp_len) ? temp_len : max_len;
        }
    }

    max_len = (max_len < len) ? len : max_len;

    return max_len;
}

int tree::num_level (int level) const
{
    int now = 0,
        number = 0;

    tree_node *curr =  nullptr;
    for (curr = root, now = 1 ; (curr != nullptr) && (now < level) ; curr = curr->right, now++)
    {
        tree_node *left = curr->left;
        if (left != nullptr)
        {
            tree temp;
            temp.root = left;
            number += temp.num_level(level - now);
            temp.root = nullptr;
        }
    }

    if ((curr != nullptr) && (level == now))
        number++;

    return number;
}

int tree::get_width () const
{
    int max_len = 0,
        len = 0,
        n = 1;

    if (root == nullptr)
        return 0;
    
    max_len = 1;
    len = 1;

    while (len != 0)
    {
        n++;
        len = num_level(n);
        max_len = (max_len < len) ? len : max_len;
    }

    return max_len;
}

// A non-null tree is assumed
int tree::depth_tree (int *max_diff) const
{
    tree tmp;
    int max_depth = 1;

    int left_level = 0;
    tree_node *child = root->left;
    if (child != nullptr)
    {
        tmp.root = child;
        left_level = tmp.depth_tree(max_diff);
        tmp.root = nullptr;
    }

    int right_level = 0;
    child = root->right;
    if (child != nullptr)
    {
        tmp.root = child;
        right_level = tmp.depth_tree(max_diff);
        tmp.root = nullptr;
    }

    int diff = 0;
    if (right_level < left_level)
    {
        diff = left_level - right_level;
        max_depth += left_level;
    } else
    {
        diff = right_level - left_level;
        max_depth += right_level;
    }
    
    *max_diff = (*max_diff < diff) ? diff : *max_diff;

    return max_depth; 
}

int tree::get_balance () const
{
    int max_diff = 0;
    
    if (root == nullptr)
        return 0;

    depth_tree(&max_diff);

    return max_diff;
}

void tree::print_stat (const char *executor, const int task, const double t) const
{
	const double eps = -1e-16;
	
	int (tree::*solves[])() const = {
		&tree::get_count_leaf,
		&tree::get_count_1,
		&tree::get_count_2,
		&tree::get_height,
		&tree::get_width,
		&tree::get_balance,
	};

	int res[7];

	res[0] = get_count_total_subtree(root);
	for (int i = 0 ; i < 6 ; ++i)
	     	res[i+1] = (this->*solves[i])();
	
	if (t < eps)
		fprintf(stdout, "%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d\n", executor, task, res[0], res[1], res[2], res[3], res[4], res[5], res[6]);
	else
		fprintf(stdout, "%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d Elapsed = %.2f\n", executor, task, res[0], res[1], res[2], res[3], res[4], res[5], res[6], t);
}
