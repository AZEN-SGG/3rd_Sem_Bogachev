#include "solve.h"

int t8_solve(student *arr, int n, student& x)
{
	int len_del = 0,
	    len_desc = 0;

	for (int i = 0; i < n; ++i)
	{
		if (arr[i] > x)
			len_desc++;
		else {
			if (len_desc) {
				arr[i - len_desc - len_del + (len_desc > 1)] = (student&&)arr[i - 1];
				arr[i - len_desc - len_del] = (student&&)arr[i - len_desc];
				len_del += len_desc - 1 - (len_desc > 1);
				len_desc = 0;
			} if (len_del)
				arr[i - len_del] = (student&&)arr[i];
		}
	}

	if (len_desc) {
		arr[n - len_desc - len_del + (len_desc > 1)] = (student&&)arr[n - 1];
		arr[n - len_desc - len_del] = (student&&)arr[n - len_desc];
		len_del += len_desc - 1 - (len_desc > 1);
	}

	return n - len_del;
}

