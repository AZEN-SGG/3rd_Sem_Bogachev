#pragma once

#include "b_tree.h"

template <typename T>
int b_tree<T>::get_number_elem_in_subtree (const b_tree_node<T> *curr)
{
	int number = curr->size;

	for (int i = 0 ; i <= curr->size ; ++i)
	{
		if (!curr->children[i])
			break;

		number += get_number_elem_in_subtree(curr->children[i]);
	}

	return number;
}

template <typename T>
int b_tree<T>::t6_solve (const int k) const
{
	if (!root)
		return 0;

	int depth = get_depth_subtree(root);
	if (depth != k)
		return 0;

	return get_number_elem_in_subtree(root);
}

