#include "array.h"

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
