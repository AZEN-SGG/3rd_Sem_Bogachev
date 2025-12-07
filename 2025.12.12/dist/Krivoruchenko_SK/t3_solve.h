#pragma once

#include "rb_tree.h"

template <typename T>
int rb_tree<T>::get_number_elem_in_subtrees_with_less_k_nodes_in_each_level (const rb_tree_node<T> *curr, const int k, int &count)
{
	int	left_count = 0,
		right_count = 0,
		left_number = 0,
		right_number = 0;

	int number_on_level = 1,
		level = 0,
		number = 0;
	while ((number_on_level <= k) && (number_on_level))
	{
		count += number_on_level;
		level++;
		number_on_level = get_number_elem_on_level(curr, level);
	}

	if (number_on_level)
	{
		if (curr->left)
			left_number = get_number_elem_in_subtrees_with_less_k_nodes_in_each_level(curr->left, k, left_count);

		if (curr->right)
			right_number = get_number_elem_in_subtrees_with_less_k_nodes_in_each_level(curr->right, k, right_count);

		number = left_number + right_number;
	} else
		number = count;

	return number;
}

template <typename T>
int rb_tree<T>::t3_solve (const int k) const
{
	if (!root || k < 1)
		return 0;

	int count = 0;
	return get_number_elem_in_subtrees_with_less_k_nodes_in_each_level(root, k, count);
}

