#include "list.h"

list_node * list::quicksort (int len)
{
    list L, M, U;
    list_node *border_left = nullptr,
              *border_right = nullptr,
              *new_head = nullptr,
              *new_end = nullptr;

    while ((head != nullptr) && (head->next != nullptr))
    {
        list_node *curr = nullptr,
                  *next = nullptr,
                  *medium = head;

        // Choose M 
        len >>= 1;

        if (len == 0)
            head = head->next;
        else
        {
            for (int i = 0 ; i < (len - 1) ; ++i, medium = medium->next);
            
            curr = medium->next; // Use like temp
            medium->next = curr->next; // curr != nullptr because while check it
            medium = curr;
        }

        M.head = medium;
        medium->next = nullptr;
        list_node *end_l = nullptr,
                  *end_m = medium,
                  *end_u = nullptr;
        int len_l = 0,
            len_m = 1,
            len_u = 0;
        for (curr = head ; (curr != nullptr) ; curr = next)
        {
            next = curr->next;
    
            int cmp = medium->cmp(*curr);
            if (cmp > 0)
            {
                if (end_l != nullptr)
                    end_l->next = curr;
                else
                    L.head = curr;
                curr->next = nullptr;
                end_l = curr;
                len_l++;
            } else if (cmp < 0)
            {
                if (end_u != nullptr)
                    end_u->next = curr;
                else
                    U.head = curr;
                curr->next = nullptr;
                end_u = curr;
                len_u++;
            } else
            {
                end_m->next = curr;
                curr->next = nullptr;
                end_m = curr;
                len_m++;
            }
        }
    
        // Reqursive
        if (len_l < len_u)
        {
            if (len_l > 1)
                end_l = L.quicksort(len_l);

            list_node *left = nullptr;
    
            if (len_l != 0)
            {
                end_l->next = M.head;
                left = L.head;
            } else
                left = M.head;

            if (border_left != nullptr)
                border_left->next = left;
            else
                new_head = left;

            border_left = end_m;

            len = len_u;
            head = U.head;
        } else if (len_l > 0)
        {
            if (len_u > 1)
                end_u = U.quicksort(len_u);

            if (len_u != 0)
            {
                if (border_right == nullptr)
                    new_end = end_u;
                else
                    end_u->next = border_right;
                border_right = U.head;
            } else if (border_right == nullptr)
                new_end = end_m;
            
            end_m->next = border_right;
            border_right = M.head;

            len = len_l;
            head = L.head;
        } else
        {
            if (border_left != nullptr)
                border_left->next = M.head;
            else
                new_head = M.head;

            if (border_right == nullptr)
                new_end = end_m;
            else
                end_m->next = border_right;
            
            len = 0;
            head = nullptr;
        }

        L.head = nullptr;
        M.head = nullptr;
        U.head = nullptr;
    }

    if (head != nullptr)
    {
        if (border_right == nullptr)
            new_end = head;
        else
            head->next = border_right;
    
        if (border_left != nullptr)
        {
            border_left->next = head;
            head = new_head;
        }
    } else // Checking for the end is not necessary, since it definitely exists.
        head = new_head;

    return new_end;
}

