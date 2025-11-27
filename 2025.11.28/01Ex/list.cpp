#include "list.h"

template <typename T>
io_status list2<T>::read (FILE *fp)
{
	list2_node<T> buf,
		*prev = nullptr,
		*next = nullptr;
	io_status ret;

	erase();

	if ((ret = buf.read(fp)) != io_status::success)
		return ret;

	head = new list2_node<T>;
	if (head == nullptr)
		return io_status::memory;

	*head = (list2_node<T> &&)buf;
	list2_node<T> *curr = head;

	unsigned int i = 0;
	while ((buf.read(fp) == io_status::success) && (i < m))
	{
		next = new list2_node<T>;

		if (next == nullptr)
		{
			erase();
			return io_status::memory;
		}

		*next = (list2_node<T> &&)buf;
		
		curr->prev = prev;
		curr->next = next;

		prev = curr;
		curr = next;
	} if ((!feof(fp)) && (i < m))
	{
		erase();
		return io_status::format;
	}

	curr->prev = prev;
	curr->next = nullptr;

	return io_status::success;
}

template <typename T>
void list2<T>::del_node (list2_node<T> *el)
{
	if (!el)
		return;

	list2_node<T> *prev = el->prev,
		   *next = el->next;

	if (next)
		next->prev = prev;
	
	if (prev)
		prev->next = next;
	else
		head = next;

	delete el;
}

/*
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
*/
