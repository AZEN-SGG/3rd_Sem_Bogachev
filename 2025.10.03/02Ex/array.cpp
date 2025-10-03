#include "array.h"

int init_students (student *arr, int n, int s, const char *name)
{	
	if (s == 0) {
		io_status ret = read_students(arr, n, name);
		do {
			switch (ret)
			{
				case io_status::success:
					continue;
				case io_status::open:
					fprintf (stderr, "Cannot open %s\n", name);
					break;
				case io_status::format:
					fprintf (stderr, "Wrong format of file %s\n", name);
					break;
				case io_status::eof:
					fprintf (stderr, "End of file %s\n", name);
					break;
				case io_status::memory:
					fprintf (stderr, "Memory error\n");
					break;
			}

			return 1;
		} while (0);
	} else
		for (int i = 0; i < n; ++i)
			arr[i].init_f(s, n, i+1);

	return 0;
}

io_status read_students (student *arr, int n, const char *name)
{
	io_status io_err;
	FILE *fp = nullptr;
	if (!(fp = fopen(name, "r")))
		return io_status::open;

	for (int i = 0; i < n; i++) 
	{
		if ((io_err = arr[i].read(fp)) != io_status::success) {
			fclose(fp);
			return io_err;
		}
	}

	fclose(fp);
	return io_status::success;
}

void print_students (const student *arr, int n, int p)
{
	for (int i = 0; i < (n < p ? n : p) ; ++i) 
		arr[i].print();
}

int diff_array (const student *arr, const int n)
{
	int count = 0;
	for (int i = 1; i < n; ++i)
		count += (arr[i] < arr[i - 1]);
	return count;
}
