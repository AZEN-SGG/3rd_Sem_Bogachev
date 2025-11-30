#pragma once

#include "b_tree.h"

template <typename T>
t_count b_tree<T>::get_number_elem_in_subtrees_with_less_k_nodes (const b_tree_node<T> *curr, const int k)
{
	t_count answer{};

	for (int i = 0 ; i <= curr->size ; ++i)
	{
		if (!curr->children[i])
			break;

		t_count temp = get_number_elem_in_subtrees_with_less_k_nodes(curr->children[i], k);
		answer.answer += temp.answer;
		answer.count += temp.count;
	}

	answer.count++;

	if (answer.count <= k)
		answer.answer += curr->size;

	return answer;
}

template <typename T>
int b_tree<T>::t2_solve (const int k) const
{
	if (!root)
		return 0;
	
	return get_number_elem_in_subtrees_with_less_k_nodes(root, k).answer;
}

