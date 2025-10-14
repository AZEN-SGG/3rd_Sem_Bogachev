#include "solve_01.h"

int t1_solve(list_node *node)
{
	list_node *maximum = node;
	int number = 1;

	for (node = node->get_next() ; node != nullptr ; node = node->get_next())
	{
		if (*maximum < *node)
		{ maximum = node; number = 1; }
		else if (*maximum == *node)
			number++;
	}

	return number;
}

