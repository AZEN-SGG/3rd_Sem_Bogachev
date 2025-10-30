#include "list.h"
#include "io_status.h"

#include <cstdio>

void list::erase ()
{
	list_node *next;
	for (list_node *curr = head; curr; curr = next)
	{
		next = curr->next;
		delete curr;
	}
    
    head = nullptr;
}

void list::print (const unsigned int r, FILE *fp) const
{
	unsigned int i = 0;
	for (const list_node *curr = head; ((curr != nullptr) && (i < r)); curr = curr->next)
	{
		curr->print(fp);
		i++;
	}
}

io_status list::read (FILE *fp, const unsigned int max_read)
{
	list_node buf, *tail;
    unsigned int i = 0;
	io_status ret;

	if ((ret = buf.read(fp)) != io_status::success)
		return ret;

	head = new list_node;
	if (head == nullptr)
		return io_status::memory;

	*head = (list_node&&)buf;
	list_node *curr = head;

	while ((i < max_read) && (buf.read(fp) == io_status::success))
	{
		tail = new list_node;

		if (tail == nullptr)
		{
			erase();
			return io_status::memory;
		}

		*tail = (list_node&&)buf;
		curr->next = tail;
		curr = tail;
        
        i++;
	} if ((i < max_read) && (!feof(fp)))
	{
		erase();
		return io_status::format;
	}

	return io_status::success;
}

io_status list::read_file (const char *filename)
{
	FILE *fp = fopen(filename, "r");

	if (fp == nullptr)
		return io_status::open;
	
	io_status ret = read(fp);
	
	fclose(fp);
	return ret;	
}

void list::add_to_top (list_node *new_head)
{
    new_head->next = head;
    head = new_head;
}

int list::num_diff () const
{
    int diff = 0;
    list_node *curr = head,
              *next = nullptr;

    if (curr == nullptr)
        return 0;

    for (next = curr->next ; (next != nullptr) ; next = curr->next)
    {
        if (*curr > *next)
            diff++;

        curr = next;
    }

    return diff;
}

