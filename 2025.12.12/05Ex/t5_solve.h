#pragma once

#include "rb_tree.h"

template <typename T>
int rb_tree<T>::get_black_length (const rb_tree_node<T> *curr)
{
	int number = 0;

	for (; curr ; curr = curr->left)
		number += (curr->color == rb_tree_node<T>::colors::black);

	return number;
}

template <typename T>
int rb_tree<T>::get_number_elem_on_branch_length_k (const rb_tree_node<T> *curr, const int k)
{
	int number = 0;

	if (k <= 0)
	{
		if ((!curr->left) && (!curr->right))
			number = 1;
	} else
	{
		if (curr->left)
			number += get_number_elem_on_branch_length_k(curr->left, k - 1);

		if (curr->right)
			number += get_number_elem_on_branch_length_k(curr->right, k - 1);
		
		number += (number != 0);
	}

	return number;
}

template <typename T>
int rb_tree<T>::t5_solve (const int k) const
{
	if (k < 0)
		return 0;

	int black_length = get_black_length(root);
	if (black_length > k)
		return 0;

	return get_number_elem_on_branch_length_k(root, k - 1);
}

