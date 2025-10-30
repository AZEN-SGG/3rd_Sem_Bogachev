#include "list.h"

void list::add_to_sorted (list_node *new_node)
{
	list_node *curr = nullptr,
		  *prev = nullptr;

	for (curr = head ; (curr != nullptr) ; prev = curr, curr = curr->next)
	{
		if (*curr >= *new_node)
				break;
	}

	if (prev == nullptr)
	{
		head = new_node;
		new_node->next = curr;
	} else
	{
		prev->next = new_node;
		new_node->next = curr;
	}
}

void list::line_insert_sort ()
{
    list sorted;
    list_node *next = nullptr,
              *curr = head->next;

    sorted.add_to_sorted(head);

    for (; (curr != nullptr) ; curr = next)
    {
	    next = curr->next;
	    sorted.add_to_sorted(curr);
    }

    head = nullptr;
    *this = (list&&)sorted;
}
