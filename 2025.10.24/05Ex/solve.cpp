#include "list.h"

void list2::t5_solve (int k)
{
	int len = 0;
	list2_node *curr = nullptr,
		   *next = nullptr;

	for (curr = head ; curr != nullptr ; curr = next)
	{
		next = curr->get_next();
		if (next == nullptr)
			return;

		if (*head == *next)
		{
			len++;
		} else
		{
			if (len)
			{
				del_nodes(
			}
		}
	}

	if (curr == nullptr)
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
		} else // start <= start_next
		{
			if (i == k)
			{
				del_node(start);
			} else
			{
				i++;
			}
		}

		if (curr_next == nullptr) // Сначала удаление максимума, потом проверка на следующий
			return;

		if (*curr < *curr_next) // Обратное условие -> точно не максимум предыдущие к - 1
			i = 0;

		start = start_next;
		curr = curr_next;
	}
}
