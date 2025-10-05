#include "solve.h"

int t6_solve(student *arr, int n, student& x)
{
	int len_del = 0;

	for (int i = 0; i < n; ++i)
	{
		if (arr[i] < x)
			len_del++;
		else if (len_del)
			arr[i - len_del] = (student&&)arr[i];
	}

	return n - len_del;
}

