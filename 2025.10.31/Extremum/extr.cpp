#include "list.h"

/*
void list::minimum (list_node **prev_min, list_node **min)
{
    list_node *prev = nullptr,
              *curr = nullptr,
              *next = nullptr,
              *temp = nullptr;
    list old,
         young;

    prev = old->head;
    curr = prev->next;

    if (curr == nullptr)
        break;

    next = curr->next;

    if (*prev < *curr)
    {
        old->head = curr;
        young.append(prev);
    } else
    {
        prev->next = next;
        young.append(curr);
    }

    for (curr = next; (curr != nullptr) ; prev = curr, curr = next)
    {
        next = curr->next;
        if (next == nullptr)
        {
            prev->next = nullptr;
            young.append(curr);
            curr = prev;
            break;
        }

        if (*curr < *next)
        {
            prev->next = next;
            young.append(curr);
            curr = next;
            next = next->next;
        } else
        {
            curr->next = next->next;
            young.append(next);
            next = curr->next;
        }
    }
    
    if (old != this)
    {
        this->head
    }

}
*/
