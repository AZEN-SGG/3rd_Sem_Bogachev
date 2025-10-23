#include "list.h"

void list2::erase ()
{
	list2_node *next = nullptr;
	for (list2_node *curr = head ; curr != nullptr ; curr = next)
	{
			next = curr->get_next();
			delete curr;
	}

	head = nullptr;
}

io_status list2::read (FILE *fp, unsigned int max_read)
{
	list2_node buf,
		*prev = nullptr,
		*next = nullptr;
	io_status ret;

	erase();

	if ((ret = buf.read(fp)) != io_status::success)
		return ret;

	head = new list2_node;
	if (head == nullptr)
		return io_status::memory;

	*head = (list2_node &&)buf;
	list2_node *curr = head;

	unsigned int i = 0;
	while ((buf.read(fp) == io_status::success) && (i < max_read))
	{
		next = new list2_node;

		if (next == nullptr)
		{
			erase();
			return io_status::memory;
		}

		*next = (list2_node &&)buf;
		
		curr->set_prev(prev);
		curr->set_next(next);

		prev = curr;
		curr = next;
	} if ((!feof(fp)) && (i < max_read))
	{
		erase();
		return io_status::format;
	}

	curr->set_prev(prev);
	curr->set_next(nullptr);

	return io_status::success;
}

io_status list2::read_file (char *filename, unsigned int max_read)
{
	FILE *fp = fopen(filename, "r");

	if (fp == nullptr)
		return io_status::open;

	io_status ret = read(fp, max_read);

	fclose(fp);
	return ret;
}

void list2::del_node (list2_node *el)
{
	if (el == nullptr)
		return;

	list2_node *prev = el->get_prev(),
		   *next = el->get_next();

	if (next != nullptr)
		next->set_prev(prev);
	
	if (prev != nullptr)
		prev->set_next(next);
	else
		head = next;

	delete el;
}

void list2::del_nodes_after (list2_node *start, int len)
{
	list2_node *prev = start->get_prev(),
		   *next = nullptr;
	
	for (; (start != nullptr) && (len > 0) ; start = next)
	{
		next = start->get_next();
		delete start;
		len--;
	}

	if (start != nullptr)
		start->set_prev(prev);

	if (prev != nullptr)
		prev->set_next(start);
	else
		head = start;
}

void list2::del_nodes_before (list2_node *end, int len)
{
	list2_node *prev = nullptr,
		   *next = end;

	for (end = end->get_prev() ; (end != nullptr) && (len > 0) ; end = prev)
	{
		prev = end->get_prev();
		delete end;
		len--;
	}

	if (end != nullptr)
		end->set_next(next);
	else
		head = next;

	if (next != nullptr)
		next->set_prev(end);
}

void list2::print (unsigned int r, FILE *fp) const
{
	unsigned int i = 0;
	for (const list2_node *curr = head ; ((curr != nullptr) && (i < r)) ; curr = curr->get_next())
	{
		curr->print(fp);
		i++;
	}
}

unsigned int list2::get_length ()
{
	unsigned int len = 0;
	for (list2_node *curr = head ; curr != nullptr ; curr = curr->get_next())
		len++;
	return len;
}
