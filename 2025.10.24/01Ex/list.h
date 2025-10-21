#ifndef LIST_H
#define LIST_H

#include "student.h"

class list2_node : public student
{
	private:
		list2_node * next = nullptr;
		list2_node * prev = nullptr;
	public:
		friend class list2;
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
		
		void print (unsigned int r = 10, FILE *fp = stdout) const;
		unsigned int get_length ();

		
}

#endif // LIST_H