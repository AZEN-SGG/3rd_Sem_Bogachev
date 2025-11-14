#include "solve_02.h"

family tree::find_min_level_subtree (tree_node *curr, level_adds adds)
{
	family min;
    min.child = nullptr;

	for (; (curr != nullptr) ; curr = curr->right, adds.c_level++)
	{
		int c_child = adds.pos << 1;
		
		if ((adds.c_level + 1) == adds.n_level)
		{
			tree_node *child;
            int dir;
			if (c_child > adds.min_el)
			{
				if (curr->left == nullptr)
                {
					child = curr->right;
                    dir = 1;
                } else if (curr->right == nullptr)
				{
                    child = curr->left;
                    dir = 0;
                } else if (curr->left->value < curr->right->value)
                {
					child = curr->left;
                    dir = 0;
                } else
                {
                    child = curr->right;
                    dir = 1;
                }
			} else
            {
				child = curr->right;
                dir = 1;
            }

			if ((min.child == nullptr) || ((child != nullptr) && (child->value < min.child->value)))
			{
				min.parent = curr;
				min.child = child;
                min.dir = dir;
			}

			break;
		} else
		{
            int max_el = (c_child << (adds.n_level - adds.c_level - 1)) + (1 << (adds.n_level - adds.c_level - 1)) - 1;
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

family tree::get_node_by_index (bin_pos pos) const
{
    pos.index -= 1 << pos.level;
    pos.level--;

    int dir = 0;
    tree_node *curr = root,
              *prev = nullptr;
    while (pos.level >= 0 && curr != nullptr)
    {
        prev = curr;

        if (pos.index < (1 << pos.level))
        {
            curr = curr->left;
            dir = 0;
        } else
        {
            curr = curr->right;
            dir = 1;
            pos.index -= (1 << pos.level);
        }

        pos.level--;
    }

    family node;
    node.parent = prev;
    node.child = curr;
    node.dir = dir;

    return node;
}

void tree::t2_solve ()
{
    int index = 1,
        level = 0,
        was = 1;

    family min, curr;

    curr.child = nullptr;

    do {
        do {
            index++;
            if (index >= (1 << (level + 1)))
            {
                if (was == 0)
                    break;
                was = 0;
                level++;
            }

            bin_pos pos {
                index,
                level,
            };
            curr = get_node_by_index(pos);
        } while (curr.child == nullptr);
        if (curr.child == nullptr)
            break;

        was++;

        level_adds adds {
            1, // from root
            0,
            level, // what need
            index - 1,
        };

        min = find_min_level_subtree(root, adds);

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
    } while (true);
}

