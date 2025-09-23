#include "solve.h"

void t5_solve(data *a, int n)
{
	int i, min;
	for (i=0; i < n-1; ++i)
	{
		min = minimum(a+i, n-i)+i;
		std::swap(a[i], a[min]);
	}
}

int minimum(data *a, int n)
{
	int i, min=0;
	for (i = 1; i < n; ++i)
		if (a[min] > a[i]) 
			min = i;

	return min;
}

