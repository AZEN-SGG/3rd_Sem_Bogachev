#include "list.h"

void list2::t2_solve (int k)
{
	list2_node *last = head;
	for (; last->get_next() != nullptr ; last = last->get_next());

	for (list2_node *curr = last ; curr != nullptr ;)
	{
		int i = 0;
		list2_node *prev = curr->get_prev();
		for (; (prev != nullptr) && (i < k) ; prev=prev->get_prev())
		{
			if (curr > prev)
				break;
			i++;
		} if ((prev != nullptr) && (i < k))
		{
			prev = curr->get_prev();
			list2_node *next = curr->get_next();
			prev->set_next(next);
			if (next != nullptr)
				next->set_prev(prev);
			delete curr;
			curr = prev;
		} else
			curr = curr->get_prev();
	}
}
