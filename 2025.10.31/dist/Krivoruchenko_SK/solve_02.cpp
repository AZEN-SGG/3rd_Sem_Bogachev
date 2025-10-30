#include "list.h"

void list::find_min_sort ()
{
    list sorted;
    list_node *prev = nullptr,
              *curr = nullptr,
              *p_low = nullptr,
              *low = nullptr,
              *s_end = nullptr;

    while (head != nullptr)
    {
        prev = head;

        p_low = nullptr;
        low = head;

        for (curr = head->next ; (curr != nullptr) ; prev = curr, curr = curr->next)
        {
            if (*curr < *low)
            {
                p_low = prev;
                low = curr;
            }
        }

        if (p_low == nullptr)
            head = low->next;
        else
            p_low->next = low->next;
    
        if (s_end == nullptr)
            sorted.head = low;
        else
            s_end->next = low;
        
        s_end = low;
        s_end->next = nullptr;
    }

    *this = (list&&)sorted;
}
