#pragma once

#include "rb_tree.h"

template <typename T>
int rb_tree<T>::get_number_elem_in_subtrees_with_level_less_k (const rb_tree_node<T> *curr, const int k, int &level)
{
	int number = 1,
		left_level = 0,
		right_level = 0;

	if (curr->left)
		number += get_number_elem_in_subtrees_with_level_less_k(curr->left, k, left_level);

	if (curr->right)
		number += get_number_elem_in_subtrees_with_level_less_k(curr->right, k, right_level);

	level = 1 + ((left_level < right_level) ? right_level : left_level);

	if (level > k)
		number--;

	return number;
}

template <typename T>
int rb_tree<T>::t2_solve (const int k) const
{
	if (!root || k < 1)
		return 0;

	int level = 0;
	
	return get_number_elem_in_subtrees_with_level_less_k(root, k, level);
}

