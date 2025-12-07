#pragma once

#include "rb_tree.h"

template <typename T>
int rb_tree<T>::get_number_elem_on_level (const rb_tree_node<T> *curr, const int level)
{
	if (!level)
		return 1;

	int number = 0;
	if (curr->left)
		number += get_number_elem_on_level(curr->left, level - 1);

	if (curr->right)
		number += get_number_elem_on_level(curr->right, level - 1);

	return number;
}

template <typename T>
int rb_tree<T>::t4_solve (const int k) const
{
	if (k < 0)
		return 0;

	return get_number_elem_on_level(root, k);
}

