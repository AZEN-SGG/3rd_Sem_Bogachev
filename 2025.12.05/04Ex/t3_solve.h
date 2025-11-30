#pragma once

#include "b_tree.h"

template <typename T>
int b_tree<T>::get_depth_subtree (const b_tree_node<T> *curr)
{
	int depth;
	for (depth = 0 ; curr ; curr = curr->children[0], depth++);
	return depth;
}

template <typename T>
int b_tree<T>::get_number_elem_in_subtrees_with_less_k_levels (const b_tree_node<T> *curr, const int k, const int level)
{
	int count = 0;

	for (int i = 0 ; i <= curr->size ; ++i)
	{
		if (!curr->children[i])
			break;

		count += get_number_elem_in_subtrees_with_less_k_levels(curr->children[i], k, level - 1);
	}

	if (level <= k)
		count += curr->size;

	return count;
}

template <typename T>
int b_tree<T>::t3_solve (const int k) const
{
	int depth = get_depth_subtree(root);
	if (!depth)
		return 0;
	
	if (depth == 1 && depth <= k)
		return root->size;
	
	return get_number_elem_in_subtrees_with_less_k_levels(root, k, depth);
}

