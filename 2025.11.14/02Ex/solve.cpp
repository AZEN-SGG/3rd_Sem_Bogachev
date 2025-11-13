#include "solve.h"

family tree::find_min_level_subtree (tree_node *curr, level_adds adds)
{
	family min;
    min.child = nullptr;

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
					child = (curr->left->value < curr->right->value) ? curr->left : curr->right;
			} else
				child = curr->right;

			if ((min.child == nullptr) || ((child != nullptr) && (child->value < min.child->value)))
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
				if ((min.child == nullptr) || ((temp.child != nullptr) && (temp.child->value < min.child->value)))
					min = temp;
			}

			adds.pos = c_child + 1; // right
		}
	}

	return min;
}

family tree::get_index_node (int n, int level) const
{
    family needed;
    tree_node *curr = root;

    needed.parent = root;

    int diff_levels = (1 << level);
    n -= diff_levels;
    diff_levels >>= 1;

    while ((diff_levels > 0) && (curr != nullptr))
    {
        if (diff_levels == 1) // Before needed
            needed.parent = curr;

        if (n >= (diff_levels))
        {
            curr = curr->right;
            needed.dir = 1;
            n -= diff_levels;
        } else
        {
            curr = curr->left;
            needed.dir = 0;
        }

        diff_levels >>= 1;
    }

    needed.child = curr;

    return needed;
}

void tree::t2_solve ()
{
    int index = 2,
        level = 1;

    family min, curr;

    do {
        level_adds adds {
            1, // from root
            0,
            level, // what need
            index - 1,
        };

        min = find_min_level_subtree(root, adds);
        if (min.child == nullptr)
            break;
        
        do {
            curr = get_index_node(index, level);
            index++;
            level += (index >= (1 << (level + 1)));
        } while (curr.child == nullptr);

        if (curr.child != min.child)
        {
            tree_node *temp = curr.child->left;
            curr.child->left = min.child->left;
            min.child->left = temp;
            
            temp = curr.child->right;
            curr.child->right = min.child->right;
            min.child->right = temp;

            if (curr.dir)
                curr.parent->right = min.child;
            else
                curr.parent->left = min.child;

            if (min.dir)
                min.parent->right = curr.child;
            else
                min.parent->left = curr.child;
        }
    } while (min.child != nullptr);
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

