#include "solve.h"

void t6_solve(data *arr, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int index = find(arr, i, arr[i]);
		if (index != i)
			append(arr, i+1, arr[i], index);
	}
}

int find(data *arr, int n, data& x)
{
	int i;
	for (i = 0 ; i < n; ++i)
		if (x < arr[i])
			break;
	return i;
}

void append(data *arr, int n, data x, int index)
{
	for (int i = n-1; i > index; --i)
		arr[i] = arr[i-1];
	arr[index] = x;
}

