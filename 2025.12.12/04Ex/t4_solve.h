#pragma once

#include "rb_tree.h"

template <typename T>
int rb_tree<T>::get_number_elem_on_level (const rb_tree_node<T> *root, int level)
{
	const rb_tree_node<T> *curr = root;
	int number = 0,
		flag = 0;

	if (!root)
		return 0;

	while (curr != root->parent)
	{
		if (!level)
		{
			number++;

			flag = 1 + (curr->parent && (curr == curr->parent->right));
			curr = curr->parent;
			level++;
		} else
		{
			if (curr->left && flag == 0)
			{
				curr = curr->left;
				level--;
			} else if (curr->right && flag != 2)
			{
				flag = 0;
				curr = curr->right;
				level--;
			} else
			{
				flag = 1 + (curr->parent && (curr == curr->parent->right));
				curr = curr->parent;
				level++;
			}
		}
	}

	return number;
}

template <typename T>
int rb_tree<T>::t4_solve (const int k) const
{
	if (k < 0)
		return 0;

	return get_number_elem_on_level(root, k);
}

