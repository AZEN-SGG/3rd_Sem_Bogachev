#include "solve.h"

family tree::find_min_level_subtree (tree_node *curr, level_adds adds)
{
	family min;

	for (; (curr != nullptr) ; curr = curr->right, adds.c_level++)
	{
		int c_child = ((1 << (adds.c_level + 1)) + (((1 << (adds.c_level)) ^ adds.pos) << 1));
		
		if ((adds.c_level + 1) == adds.n_level)
		{
			tree_node *child;
			if (c_child > adds.min_el)
			{
				if (curr->left == nullptr)
					child = curr->right;
				else if (curr->right == nullptr)
					child = curr->left;
				else
					child = (*(curr->left) < *(curr->right)) ? curr->left : curr->right;
			} else
				child = curr->right;

			if ((min.child == nullptr) || ((child != nullptr) && (*child < *min.child)))
			{
				min.parent = curr;
				min.child = child;
			}

			break;
		} else
		{
            int max_el = (((c_child + 1) * (1 << (adds.n_level - adds.c_level - 1))) - 1);
			if ((curr->left != nullptr) && (max_el > adds.min_el))
			{
				level_adds temp_adds {
					c_child, // left
					adds.c_level + 1,
					adds.n_level,
					adds.min_el,
				};
				family temp = find_min_level_subtree(curr->left, temp_adds);
				if ((min.child == nullptr) || ((temp.child != nullptr) && (*temp.child < *min.child)))
					min = temp;
			}

			adds.pos = c_child + 1; // right
		}
	}

	return min;
}

void tree::test ()
{
	level_adds temp {
		1,
		0,
		2,
		5,
	};

	family ans = find_min_level_subtree(root, temp);

	printf("Minimum is:\n");
	ans.child->print();
	printf("Father is\n");
	ans.parent->print();
}

