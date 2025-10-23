#include "list.h"

void list2::t3_solve (int k)
{
	for (list2_node *curr = head ; curr != nullptr ;)
	{
		int i = 0;
		list2_node *next = curr->get_next();
		for (; (next != nullptr) && (i < k) ; next=next->get_next())
		{
			if (*curr > *next)
				break;
			i++;
		} if ((next != nullptr) && (i < k))
		{
			next = curr->get_next();
			list2_node *prev = curr->get_prev();
			next->set_prev(prev);
			if (prev != nullptr)
				prev->set_next(next);
			else
				head = next;
			delete curr;
			curr = next;
		} else
			curr = curr->get_next();
	}
}
