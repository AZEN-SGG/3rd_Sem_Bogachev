#ifndef LIST_H
#define LIST_H

template <typename T>
class list2;

template <typename T>
class list2_node : public T
{
	private:
		list2_node * next = nullptr;
		list2_node * prev = nullptr;
	public:
		list2_node () = default;
		~list2_node () { next = nullptr; prev = nullptr; }

		list2_node (const list2_node&) = delete;
		list2_node (list2_node&& r) : T((T&&)r)
		{
			prev = r.prev;
			r.prev = nullptr;

			next = r.next;
			r.next = nullptr;
		}

		list2_node& operator= (const list2_node&) = delete;
		list2_node& operator= (list2_node&& r)
		{
			*(T *)(this) = (T&&)r;
			
			prev = r.prev;
			r.prev = nullptr;

			next = r.next;
			r.next = nullptr;
			return *this;
		}

		list2_node * get_next () const { return next; }
		list2_node * get_prev () const { return prev; }

		void set_next (list2_node *r) { next = r; }
		void set_prev (list2_node *r) { prev = r; }

		friend class list2<T>;
};

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

		io_status read (FILE *fp = stdin);
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
			unsigned int i = 0;
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

#endif // LIST_H
