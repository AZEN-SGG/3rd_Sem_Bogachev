#pragma once

#include "b_tree.h"

template <typename T>
int b_tree<T>::get_number_nodes_on_level_subtree (const b_tree_node<T> *curr, const int level)
{
	if (!level)
		return 1;

	int number = 0;

	for (int i = 0 ; i <= curr->size ; ++i)
	{
		if (!curr->children[i])
			break;

		number += get_number_nodes_on_level_subtree(curr->children[i], level - 1);
	}

	return number;
}

template <typename T>
t_count b_tree<T>::get_number_elem_in_subtrees_with_less_k_nodes_in_level (const b_tree_node<T> *curr, const int k, int &count, const int depth)
{
	t_count answer{};

	for (int i = 0 ; i <= curr->size ; ++i)
	{
		if (!curr->children[i])
			break;

		int temp_count = 0;
		t_count temp = get_number_elem_in_subtrees_with_less_k_nodes_in_level(curr->children[i], k, temp_count, depth - 1);
		answer.answer += temp.answer; // Number elements
		answer.count += temp.count; // Number of suitable nodes
		count += temp_count; // Number of all nodes in subtree
	}
	
	if (count++ != answer.count)
		return answer;

	for (int i = 0 ; i < depth ; ++i)
	{
		int number = get_number_nodes_on_level_subtree(curr, i);

		if (number > k)
			return answer;
	}

	answer.answer += curr->size;
	answer.count++;

	return answer;
}

template <typename T>
int b_tree<T>::t4_solve (const int k) const
{
	if (!root)
		return 0;

	// from Solve 3
	int depth = get_depth_subtree(root),
		count = 0;

	return get_number_elem_in_subtrees_with_less_k_nodes_in_level(root, k, count, depth).answer;
}

