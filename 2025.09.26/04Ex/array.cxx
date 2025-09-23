#include "array.h"

io_status read_array(data *arr, int n, const char *name)
{
	FILE *fp = 0;
	if (!(fp = fopen(name, "r")))
		return ERROR_OPEN;

	for (int i = 0; i < n; i++) 
	{
		int c;

		if (arr[i].read(fp) < 0) {
			fclose(fp);
			return ERROR_READ;
		}

		while ((c = fgetc(fp)) != '\n' && c != EOF) {}
		
		if (c == EOF) {
			fclose(fp);
			return ERROR_READ;
		}	
	}

	fclose(fp);
	return SUCCESS;
}

void print_array (const data *arr, int n, int p)
{
	for (int i = 0; i < (n < p ? n : p) ; ++i) 
		arr[i].print();
}

int diff_array (const data *arr, const int n)
{
	int count = 0;
	for (int i = 1; i < n; ++i)
		count += (arr[i] < arr[i - 1]);
	return count;
}
