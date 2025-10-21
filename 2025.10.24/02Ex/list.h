#ifndef LIST_H
#define LIST_H

#include "student.h"

class list2_node : public student
{
	private:
		list2_node * next = nullptr;
		list2_node * prev = nullptr;
	public:
		list2_node () = default;
		~list2_node () { next = nullptr; prev = nullptr; }

		list2_node (const list2_node&) = delete;
		list2_node (list2_node&& r) : student((student&&)r)
		{
			next = r.next;
			r.next = nullptr;
		}

		list2_node& operator= (const list2_node&) = delete;
		list2_node& operator= (list2_node&& r)
		{
			*(student *)(this) = (student&&)r;

			next = r.next;
			r.next = nullptr;
			return *this;
		}

		list2_node * get_next () const { return next; }
		list2_node * get_prev () const { return prev; }

		void set_next (list2_node *r) { next = r; }
		void set_prev (list2_node *r) { prev = r; }

};

class list2
{
	private:
		list2_node * head = nullptr;
	public:
		list2 () = default;
		~list2 () { erase (); }

		void erase ();
		io_status read (FILE *fp = stdin, unsigned int max_read = -1);
		io_status read_file (char *filename, unsigned int max_read = -1);
		
		void print (unsigned int r = 10, FILE *fp = stdout) const;
		unsigned int get_length ();		
		
		void shift (int k);
		void t2_solve (int k);
};

#endif // LIST_H
