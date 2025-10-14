#include "list.h"
#include "io_status.h"

#include <cstdio>

void delete_list (list_node *head)
{
	list_node *next;
	for (list_node *curr = head; curr; curr = next)
	{
		next = curr->get_next();
		delete curr;
	}
}

void print_list (const list_node *head, const int p)
{
	int i = 0;
	for (const list_node *curr = head; ((curr != nullptr) && (i < p)); curr = curr->get_next())
	{
		curr->print();
		i++;
	}
}

io_status read_list (list_node **p_head, FILE *fp = stdout)
{
	list_node buf, *head, *tail;
	io_status ret;

	if ((ret = buf.read(fp)) != io_status::success)
		return ret;

	head = new list_node;
	if (head == nullptr)
		return io_status::memory;

	*head = (list_node&&)buf;
	list_node *curr = head;

	while (buf.read(fp) == io_status::success)
	{
		tail = new list_node;

		if (tail == nullptr)
		{
			delete_list(head);
			return io_status::memory;
		}

		*tail = (list_node&&)buf;
		curr->set_next(tail);
		curr = tail;
	} if (!feof(fp))
	{
		delete_list(head);
		return io_status::format;
	}

	*p_head = head;
	return io_status::success;
}

io_status read_file (char *filename, list_node **p_head)
{
	FILE *fp = fopen(filename, "r");

	if (fp == nullptr)
		return io_status::open;
	
	io_status ret = read_list(p_head, fp);
	
	fclose(fp);
	return ret;	
}

