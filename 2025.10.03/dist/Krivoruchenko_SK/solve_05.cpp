#include "solve_05.h"

void t5_solve(student *arr, int n)
{
	int i, min;
	for (i=0; i < n-1; ++i)
	{
		min = minimum(arr+i, n-i)+i;
		std::swap(arr[i], arr[min]);
	}
}

int minimum(student *a, int n)
{
	int i, min=0;
	for (i = 1; i < n; ++i)
		if (a[min] > a[i]) 
			min = i;

	return min;
}

