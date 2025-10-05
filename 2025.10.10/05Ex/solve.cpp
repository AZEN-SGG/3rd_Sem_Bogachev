#include "solve.h"

int t5_solve (student *arr, int n)
{
	int del_num = 0,
	    len_desc = 0; // descending

	for (int i = 0; i < n - 1; ++i)
	{
		if (arr[i] > arr[i + 1])
			len_desc++;
		else {
			if (len_desc) {
				del_num += len_desc + 1;
				len_desc = 0;
			} else 
				if (del_num)
					arr[i - del_num] = (student&&)arr[i];
		}
	}

	if (len_desc)
		del_num += len_desc + 1;
	else if (del_num)
		arr[n - 1 - del_num] = (student&&)arr[n - 1];

	return n - del_num;
}

