#include "list.h"

void list2::t8_solve (int k)
{
	int len = 0,
        flag = 0;
	list2_node *curr = nullptr,
               *next = nullptr,
               *start_area = nullptr;

	for (curr = head, next = curr->get_next() ; next != nullptr ; curr = next, next = curr->get_next())
    {
		if (*curr <= *next)
		{
            if (len == 0)
            {
                len = 2;
                start_area = curr;
            } else
                len++;
		} else
		{
			if (len)
            {
                if (flag > (k + 1))
                    del_nodes_before(start_area, flag - 1); // Удаляем участок между

                flag = 1;
                len = 0;
            } else
                flag += (flag > 0);
		}
	}

	if (len && (flag > (k + 1)))
		del_nodes_before(start_area, flag - 1);

    len = 0;
    flag = 0;
}
