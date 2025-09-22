#include "array.h"

io_status read_array(data *arr, int n, const char *name)
{
	FILE *fp = 0;
	if (!(fp = fopen(name, "r")))
		return ERROR_OPEN;

	for (int i = 0; i < n; i++) 
	{
		int len, c;
		if (!fscanf(fp, "%d", &len)) {
			fclose(fp);
			return ERROR_READ;
		}

		arr[i].set_m(len);
		c = arr[i].read(fp);
		
		if (c < 0) {
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
