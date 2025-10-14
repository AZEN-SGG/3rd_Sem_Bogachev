#include "solve.h"

int t5_solve(list_node *node)
{
	list_node *last = node;
	int number = 0,
	    maximum = 0;

	for (node = node->get_next() ; node != nullptr ; node = node->get_next())
	{
		if (*last < *node)
			number += (number > 0) ? 1 : 2;
		else {
			maximum = (maximum < number) ? number : maximum;
			number = 0;
		}

		last = node;
	}

	maximum = (maximum < number) ? number : maximum;

	return maximum;
}

