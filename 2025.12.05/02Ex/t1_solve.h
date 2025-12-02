#pragma once

#include "b_tree.h"

template <typename T>
int b_tree<T>::get_number_elem_in_nodes_with_k_children (const b_tree_node<T> *curr, const int k)
{
	int number = 0,
		count = 0;
	for (int i = 0 ; i <= curr->size ; ++i)
	{
		if (!curr->children[i])
			break;

		number += get_number_elem_in_nodes_with_k_children(curr->children[i], k);
		count++;
	}

	if (count == k)
		return number + curr->size;

	return number;
}

template <typename T>
int b_tree<T>::t1_solve (const int k) const
{
	if (!root)
		return 0;
	
	if (k != 0 && k < m + 1)
	{
		int number = 0;

		for (int i = 0 ; i <= root->size ; ++i)
			number += (root->children[i] != nullptr);

		if (number == k)
			return root->size;
		
		return 0;
	}

	return get_number_elem_in_nodes_with_k_children(root, k);
}

