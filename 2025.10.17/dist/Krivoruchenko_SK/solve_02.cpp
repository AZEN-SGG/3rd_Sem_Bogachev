#include "solve_02.h"

int t2_solve(list_node *node)
{
	list_node *last = node;
	int number = 0;

	for (node = node->get_next() ; node != nullptr ; node = node->get_next())
	{
		if (*last < *node)
			number++; 
		
		last = node; 
	}

	return number;
}

