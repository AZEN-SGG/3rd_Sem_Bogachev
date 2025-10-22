#include "list.h"

list2_node * find_start (list2_node *el, int k)
{
	list2_node *start = el->get_prev();
	for (int i = 1 ; ((start != nullptr) && (i < k)) ; start = start->get_prev(), i++);
	return start;
}

list2_node * find_end (list2_node *el, int k)
{
	list2_node *end = el->get_next();
	for (int i = 1 ; ((end != nullptr) && (i < k)) ; end = end->get_next(), i++);
	return end;
}

void list2::t4_solve (int k)
{
	list2_node *curr = find_end(head, k),
		   *start = head;

	if (curr = nullptr)
		return;

	int i = 0;
	for (; curr != nullptr ;)
	{
		list2_node *start_next = start->get_next();
		list2_node *curr_next = curr->get_next();

		if (*start > *start_next)
		{
			if (i == k)
			{
				del_node(start);
				i = 0;
			} else
			{
				i = 0;
			}

			start = start_next;
			curr = curr_next;
		} else // start <= start_next
		{
			if (i == k)
			{
				del_node(start);
			} else
			{
				i++;
			}

			start = start_next;
			curr = curr_next;
		}

		if (curr_next == nullptr) // Сначала удаление максимума, потом проверка на следующий
			return;

		if (*curr < *curr_next)
		{
			i = 1;
			start = start_next;
			curr = curr_next;
		} else


	}
}
/*
	list2_node *curr = find_end(head, k), // Идеально подходит для поиска удаляемого элемента
		   *start = head, // i - k
		   *end; // i + k

	for (;  ;)

	if (curr == nullptr)
		return;

	end = find_end(curr, k);
	
	for (; end != nullptr ;)
	{
		int cmp = 0;

		list2_node *prev = curr->get_prev(),
			   *next = curr->get_next();
		// TODO: Add after delete
		do {
			if (*next > *curr)
			{
				cmp = 1;
				break;
			} else if (*prev > *curr)
			{
				cmp = -1;
				break;
			} else
			{
				prev = prev->get_prev();
				next = prev->get_next();
			}
		} while (next != end);

		if (to_del != nullptr)
			del_node(to_del);

		if (cmp == 1)
		{
			to_del = curr;
			curr = find_start(next, k);
			if (curr == nullptr)
				return;
			end = find_end(curr, k);
			break;
		}

		if (cmp == -1)
		{
			to_del = curr;
			curr
		}
	}

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

*/

