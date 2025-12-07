#pragma once

#include "rb_tree.h"

template <typename T>
int rb_tree<T>::get_number_elem_in_subtrees_with_k_nodes (const rb_tree_node<T> *curr, const int k)
{
	int number = 0,
		left_count = 0,
		right_count = 0;

	if (curr->left)
		left_count = get_number_elem_in_subtrees_with_k_nodes(curr->left, k);

	if (curr->right)
		right_count = get_number_elem_in_subtrees_with_k_nodes(curr->right, k);

	number = left_count + right_count + 1;
	if (number > k)
		number--;

	return number;
}

template <typename T>
int rb_tree<T>::t1_solve (const int k) const
{
	if (!root)
		return 0;
	
	return get_number_elem_in_subtrees_with_k_nodes(root, k);
}

