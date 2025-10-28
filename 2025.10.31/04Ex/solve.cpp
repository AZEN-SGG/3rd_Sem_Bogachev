#include "list.h"

void list::neyman_sort ()
{
    list_node *start = nullptr,
	      *before_start = nullptr;
    int k, n;

    // Main loop
    for (k = 0, n = 1 ; (k != 1) ; k = 0; n << 1)
    {
	// Merge sorted sublists
	list sorted;
	for (start = head ; (start != nullptr) ;)
	{
		list C;
		list_node *last_add = nullptr,
			  *prev = nullptr,
			  *added = nullptr,
			  *added_next = nullptr;

		// Searching start of B
		int i, in_A;
		for (i = 0, added = start ; (added != nullptr) && (i < n - 1) ; ++i, added = added->next);

		C.head = start;
		last_add = added->next; // like temp
		added->next = nullptr; // End of the list must be nullptr
		added = last_add; // Start of B
		last_add = start; // Start for adding into A
		in_A = 0; // Index into A

		// Adding B into A
		for (i = 0 ; (i < n) && (added != nullptr) ; i++, added = added_next)
		{
			added_next = added->next;

              		list_node *curr = nullptr;
			int j;
			for (j = in_A, curr = last_add ; (j < n) && (*curr < *added) ; j++, curr = curr->next);
			if (prev != nullptr)
				prev->next = added;

			added->next = curr;
			prev = added;
			last_add = curr;
			in_A = j;

		}

		// TODO: Update before_start
	}

    	*this = (list&&)sorted;
    }

    head = nullptr;
}
