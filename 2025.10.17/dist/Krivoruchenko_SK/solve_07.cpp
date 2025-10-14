#include "solve_07.h"

int t7_solve(list_node *node)
{
	list_node *last = node;
	int len = 0,
	    stable = 1,
	    maximum = 0;

	for (node = node->get_next() ; node != nullptr ; node = node->get_next())
	{
		if (*last == *node) {
			maximum = (maximum < len) ? len : maximum;
			stable = 1;
			len = 0;
		} else {
			len += !stable;
			stable = 0;
		}

		last = node;
	}

	return maximum;
}

