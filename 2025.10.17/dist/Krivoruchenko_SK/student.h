#ifndef STUDENT_H
#define STUDENT_H

#include "io_status.h"

#include <cstring>
#include <cstdio>

#define LEN 1234
#define STUDENT_NAME "Student"

class student
{
	private:
		char *name = nullptr;
		int value = 0;
	public:
		student () = default;
		student (const student& x) = delete;
		student (const char *n, int v)
		{
			init (n, v);
		}
		student (student&& x)
		{
			name = x.name; x.name = nullptr;
			value = x.value; x.value = 0;
		}
		~student ()
		{
			erase ();
		}
		student& operator= (const student& x) = delete;
		student& operator= (student&& x)
		{
			if (this == &x)
				return *this;
			erase ();
			name = x.name; x.name = nullptr;
			value = x.value; x.value = 0;
			return *this;
		}
		int is_empty () const
		{
			return ((name == nullptr) && (value == 0));
		}
		void print () const
		{
			printf ("%s %d\n", name, value);
		}
		io_status read (FILE *fp)
		{
			char n[LEN];
			int v;

			if (fscanf (fp, "%s%d", n, &v) != 2)
			{
				if (!feof (fp))
					return io_status::format;
				return io_status::eof;
			}
			erase ();
			return init (n, v);
		}
		void init_f (const int s, const int n, const int i)
		{
			erase ();
			name = new char[sizeof(STUDENT_NAME)];
			strcpy(name, STUDENT_NAME);

			switch (s)
			{
				case 1:
					value = i;
					break;
				case 2: 
					value = n - i;
					break;
				case 3:
					value = i >> 1;
					break;
				case 4:
					value = n - (i >> 1);
					break;
			}
		}
		int cmp (const student& x) const
		{
			if (name == nullptr)
			{
				if (x.name != nullptr)
					return -1;
				return value - x.value;
			} if (x.name == nullptr)
				return 1;
			int res = strcmp (name, x.name);
			if (res)
				return res;
			return value - x.value;
		}
		int operator> (const student& x) const
		{
			return (cmp (x) > 0 ? 1 : 0);
		}
		int operator< (const student& x) const
		{
			return (cmp (x) < 0 ? 1 : 0);
		}
		int operator>= (const student& x) const
		{
			return (cmp (x) >= 0 ? 1 : 0);
		}
		int operator<= (const student& x) const
		{
			return (cmp (x) <= 0 ? 1 : 0);
		}
		int operator== (const student& x) const
		{
			return (cmp (x) == 0 ? 1 : 0);
		}
	private:
		io_status init (const char *n, int v)
		{
			value = v;
			if (n != nullptr)
			{
				size_t len = strlen (n);
				name = new char [len + 1];
				if (name != nullptr)
				{
					for (size_t i = 0; i <= len; i++)
						name[i] = n[i];
				} else
					return io_status::memory;
			} else
				name = nullptr;
			return io_status::success;
		}
		void erase ()
		{
			value = 0;
			if (name != nullptr)
			{
				delete[] name;
				name = nullptr;
			}
		}
};

#endif // student_h
