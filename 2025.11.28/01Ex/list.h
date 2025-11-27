#ifndef LIST_H
#define LIST_H

#include "student.h"
#include "list_node.h"

#include <cstdio>
#include <new>

template <typename T>
class list2
{
	private:
		list2_node<T> * head = nullptr;
		static int m;
		static int r;
	public:
		list2 () = default;
		~list2 () { erase (); }

		static void set_m (int m) { list2<T>::m = m; };
		static void set_r (int r) { list2<T>::r = r; };

		void erase ()
		{
			list2_node<T> *next = nullptr;
			for (list2_node<T> *curr = head ; curr ; curr = next)
			{
				next = curr->next;
				delete curr;
			}

			head = nullptr;
		}

		io_status read (FILE *fp = stdin)
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
	
			int i = 0;
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

				i++;
			} if ((!feof(fp)) && (i < m))
			{
				erase();
				return io_status::format;
			}

			curr->prev = prev;
			curr->next = nullptr;

			return io_status::success;
		}
		
		io_status read_file (char *filename)
		{
			FILE *fp = fopen(filename, "r");

			if (fp == nullptr)
				return io_status::open;

			io_status ret = read(fp);

			fclose(fp);
			return ret;
		}
		
		void del_node (list2_node<T> *el);

		void print (FILE *fp = stdout, int level = 0) const
		{
			int i = 0;
			for (const list2_node<T> *curr = head ; (curr && (i < r)) ; curr = curr->next)
			{
				curr->print(fp, level);
				i++;
			}
		}

		int get_length () const
		{
			int len = 0;
			for (list2_node<T> *curr = head ; curr ; curr = curr->next, len++);
			return len;
		}

		int operator< (const list2 & b) const
		{
			if (!b.head)
				return 0;
			if (!head)
				return 1;
			
			if (*head < *b.head)
				return 1;

			return 0;
		}
};

extern template class list2<student>;

#endif // LIST_H
