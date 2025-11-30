#pragma once

#include "b_tree.h"

template <typename T>
int b_tree<T>::get_number_elem_on_level_subtree (const b_tree_node<T> *curr, const int level)
{
	if (!level)
		return curr->size;

	int number = 0;

	for (int i = 0 ; i <= curr->size ; ++i)
	{
		if (!curr->children[i])
			break;

		number += get_number_elem_on_level_subtree(curr->children[i], level - 1);
	}

	return number;
}

template <typename T>
int b_tree<T>::t5_solve (const int k) const
{
	if (!root)
		return 0;

	return get_number_elem_on_level_subtree(root, k);
}

