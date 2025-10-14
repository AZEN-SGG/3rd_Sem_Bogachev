#include "solve_04.h"

int t4_solve(list_node *node)
{
	list_node *last = node;
	int number = 4;

	for (node = node->get_next() ; node != nullptr ; node = node->get_next())
	{
		int cmp = node->cmp(*last);
		
		if (cmp == 0) { 
			if (number == 4)
				number = 3;
		} else if (cmp >= 0) {
			if ((number == 3) || (number == 4) || (number == 1))
				number = 1;
			else
				number = 0;
		} else if (cmp <= 0) {
			if ((number == 3) || (number == 4) || (number == 2))
				number = 2;
			else
				number = 0;
		}

		last = node; 
	}

	return number;
}

