#include "list.h"

void list2::t5_solve (int k)
{
	int len = 0;
	list2_node *curr = nullptr,
		   *next = nullptr;

	for (curr = head, next = curr->get_next() ; next != nullptr ; curr = next, next = curr->get_next())
	{
		if (*curr == *next)
		{
			len += (len == 0) ? 2 : 1;
		} else
		{
			if (len > k)
				del_nodes_before(next, len);

			len = 0;
		}
	}

	if (len > k)
	{
		del_nodes_before(curr, len-1);
		del_node(curr);
	}
}
