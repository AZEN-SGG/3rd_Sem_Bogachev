#include "list.h"

void list2::shift (int k)
{
	unsigned int len = 0;
	list2_node *last = head;
	while (last->get_next() != nullptr)
	{
		len++;
		last = last->get_next();
	}

	len++;

	k %= len;
	k += len * (k < 0);

	if (k == 0)
		return;

	head->set_prev(last);
	last->set_next(head);
	int i = 1;
	for (; (i < k) ; last=last->get_prev())
		i++;

	last->get_prev()->set_next(nullptr);
	last->set_prev(nullptr);

	head = last;
}
