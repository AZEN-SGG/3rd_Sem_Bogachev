#include "list.h"

void list2::shift (int k = 0)
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
	
	k = len * (k >> 31) + k % len;

	if (k == 0)
		return;

	head->set_prev(last);
	int i = 1;
	for (list2_node *curr = last ; ((curr != nullptr) && (i < k)) ; curr=curr->get_prev())
		i++;

	curr->get_prev()->set_next(nullptr);
	curr->set_prev(nullptr);

	head = curr;
}
