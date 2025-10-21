#include "list.h"

void list2::shift (int k)
{
	unsigned int len = 0;
	list2_node *last = head;
	for (list2_node *curr = head ; curr != nullptr ; curr=curr->get_next())
	{
		last = curr;
		len++;
	}

	if (len == 0)
		return;
	
	k = len * (k < 0) + k % len;

	if (k == 0)
		return;

	head->set_prev(last);
	int i = 1;
	for (; ((last != nullptr) && (i < k)) ; last=last->get_prev())
		i++;

	last->get_prev()->set_next(nullptr);
	last->set_prev(nullptr);

	head = last;
}
