#include "solve_06.h"

int t6_solve(list_node *node)
{
	list_node *last = node;
	int number = 0,
	    stable = 0;

	for (node = node->get_next() ; node != nullptr ; node = node->get_next())
	{
		if (*last == *node)
			stable = 1;
		else {
			number += stable;
			stable = 0;
		}

		last = node;
	}

	number += stable;

	return number;
}

