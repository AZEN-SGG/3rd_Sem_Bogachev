#include "tree.h"

struct t_count
{
	int len;
	int max;
};

static t_count max_diff_between_subtrees_of_subtree (const tree_node<T> *curr)
{
	t_count answer = {},
			temp = {};

	if (curr->left)
	{
		t_count temp = max_diff_between_subtrees_of_subtree(curr->left);
		answer.max = temp.max;
		answer.len += temp.len;
	}

	int diff = temp.len;

	if (curr->right)
	{
		temp = max_diff_between_subtrees_of_subtree(curr->right);
		answer.max = (answer.max < temp.max) ? temp.max : answer.max;
		answer.len += temp.len;
	}
	
	diff -= temp.len;
	diff = (diff < 0) ? -diff : diff;
	answer.max = (answer.max < diff) ? diff : answer.max;

	answer.len += curr->get_length();

	return answer;
}

int t4_solve () const
{
    if (!root)
        return 0;

	return max_diff_between_subtrees_of_subtree(root).max;
}
