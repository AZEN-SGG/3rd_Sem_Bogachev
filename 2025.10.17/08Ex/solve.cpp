#include "solve.h"

int t8_solve(list_node *node)
{
	list_node *last = node;
	int len = 0,
	    len_stable = 0,
	    maximum = 0,
	    area = 0;

	for (node = node->get_next() ; node != nullptr ; node = node->get_next())
	{
		int cmp = node->cmp(*last);
		
		if (cmp != 0) {
			if ((cmp * area) >= 0) {
				if (len_stable)
					len += (len == 0) ? len_stable + 1 : len_stable;
				else
					len += (len == 0) ? 2 : 1;
			} else {
				if (len_stable)
					len += (len == 0) ? len_stable : len_stable - 1;
				maximum = (maximum < len) ? len : maximum;
				len = (len_stable == 0) ? 2 : len_stable + 1;
			}
			
			len_stable = 0;
			area = cmp;
		} else {
			len_stable += (len_stable == 0) ? 2 : 1;
		}

		last = node;
	}

	if (len_stable)
		len += (len == 0) ? len_stable : len_stable - 1;
	maximum = (maximum < len) ? len : maximum;

	return maximum;
}

