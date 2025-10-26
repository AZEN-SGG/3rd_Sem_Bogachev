#ifndef LIST_H
#define LIST_H

#include "student.h"

class list;

class list_node : public student
{
	private:
		list_node *next = nullptr;
	public:
		list_node () = default;
		~list_node () { next = nullptr; }

		list_node (const list_node&) = delete;
		list_node (list_node&& r) : student((student&&)r) 
		{ 
            next = r.next;
            r.next = nullptr;
        }

        list_node& operator= (const list_node&) = delete;
		list_node& operator= (list_node&& r)
		{
			*(student *)(this) = (student&&)r;

			next = r.next;
			r.next = nullptr;
			return *this;
		}

		list_node* get_next () const { return next; }
		void set_next (list_node *r) { next = r; }
    
        friend class list;
};

class list
{
    private:
        list_node *head = nullptr;
    public:
        list () = default;
        ~list ()
        {
            erase();
        }

        list& operator= (const list&) = delete;
        list& operator= (list&& r)
        {
            erase();

            head = r.head;
            r.head = nullptr;

            return *this;
        }

        void print (unsigned int r, FILE *fp = stdout) const;
        io_status read (FILE *fp = stdin, unsigned int max_read = -1);
        io_status read_file (const char *filename);

        int num_diff () const;

//        list_node * get_head () { return head; }
//        void set_head (list_node *new_head) { head = new_head; }

        void add_to_top (list_node *new_head);

//        int get_less_than_previous ();
        
        void bubble_sort ();
    private:
        void erase ();
};

#endif // LIST_H
