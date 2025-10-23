#include "list.h"

void list2::t7_solve (int k)
{
	int len = 0,
	    flag = 0;
	list2_node *curr = nullptr,
		   *next = nullptr,
		   *start_const = nullptr;

	for (curr = head, next = curr->get_next() ; next != nullptr ; curr = next, next = curr->get_next())
	{
		if (*curr == *next)
		{
			if (len)
				len++;
			else 
			{
				len = 2;
				start_const = curr;
			}
		} else
		{
			if (len > k)
			{
				if (flag)
					del_nodes_before(start_const, flag - 1); // flag - 1 - длина участва между участками постоянства
				flag = 1;
			} else
			{
				if (flag)
				{
                    if (len)
                        flag += len - 1;

                    flag++;
				}
			}

			len = 0;
		}
	}

	if (len > k)
		del_nodes_before(start_const, flag-1);

    len = 0;
}
