#include "solve_03.h"

int t3_solve(list_node *node)
{
	list_node *last = node;
	int number = 0,
	    last_cmp = 1;

	for (node = node->get_next() ; node != nullptr ; node = node->get_next())
	{
		if (*last >= *node)
			number += last_cmp;
		if (*last <= *node)
			last_cmp = 1;
		else
			last_cmp = 0;
		
		last = node; 
	}

	number += last_cmp;

	return number;
}

