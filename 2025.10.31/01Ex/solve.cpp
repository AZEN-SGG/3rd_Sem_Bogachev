#include "list.h"

void list::bubble_sort ()
{
    list sort_list;
    list_node *prev = nullptr,
              *curr = nullptr,
              *next = nullptr;

    for (prev = head ; (prev != nullptr) ; prev = head)
    {
        curr = prev->next;

        if (curr == nullptr)
        {
            sort_list.add_to_top(head);
            head = nullptr;
            break;
        }

        if (*prev > *curr)
        {
            head = curr;
            prev->next = curr->next;
            curr->next = prev;
            
            next = prev;
            prev = curr;
            curr = next;
        }

        for (next = curr->next ; (next != nullptr) ; next = curr->next)
        {
            if (*curr > *next)
            {
                prev->next = next;
                curr->next = next->next;
                next->next = curr;
                
                prev = curr;
                curr = next;
                next = prev;
            }
    
            prev = curr;
            curr = next;
        }

        sort_list.add_to_top(curr);
        prev->next = nullptr;
    }

    *this = (list&&)sort_list;
}
