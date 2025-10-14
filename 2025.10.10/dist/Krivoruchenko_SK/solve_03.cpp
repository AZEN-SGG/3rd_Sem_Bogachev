#include "solve_03.h"

int t3_solve (student *arr, int n)
{
	int del_num = 0;
	int is_empty = 0;
	for (int i = 1; i < n - 1; ++i)
	{
		if ((arr[is_empty ? i - 1 - del_num : i - 1] > arr[i])
		 && (arr[i + 1] > arr[i])) {
			del_num++;
			is_empty = 0;
		} else if (del_num) {
			arr[i-del_num] = (student &&)arr[i];
			is_empty = 1;
		}
	}

	arr[n - 1 - del_num] = (student&&)arr[n - 1];

	return n - del_num;
}

