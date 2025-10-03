#include "solve.h"

void t6_solve(student *arr, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int index = find(arr, i, arr[i]);
		if (index != i)
			append(arr, i+1, index);
	}
}

int find(student *arr, int n, student& x)
{
	int i;
	for (i = 0 ; i < n; ++i)
		if (x < arr[i])
			break;
	return i;
}

void append(student *arr, int n, int index)
{
	for (int i = n-1; i > index; --i)
		std::swap(arr[i], arr[i-1]);
}

