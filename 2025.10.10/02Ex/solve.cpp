#include "solve.h"

int t2_solve (student *arr, int n)
{
	int del_num = 0,
	    first_index_to = 0,
	    second_index_to = 0;
	for (int i = 2; i < n; ++i)
	{
		int to_del = (arr[i - 1] < arr[i]) && (arr[i - 2] < arr[i]);
		if (second_index_to)
			arr[i - 2 - second_index_to] = (student&&)arr[i - 2];
		second_index_to = first_index_to;
		
		if (to_del) {
			first_index_to = 0;
			del_num++;
		} else {
			first_index_to = del_num;
		}
	}
	
	if (second_index_to)
			arr[n - 2 - second_index_to] = (student&&)arr[n - 2];
	if (first_index_to)
			arr[n - 1 - first_index_to] = (student&&)arr[n - 1];

	return n - del_num;
}

