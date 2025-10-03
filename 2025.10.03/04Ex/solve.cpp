#include "solve.h"

void t4_solve(student *arr, int n)
{
	int i, j;
	for (i=n; i > 0; --i)
		for (j=0; j < i-1; ++j) 
			if (arr[j] > arr[j+1])
				std::swap(arr[j], arr[j+1]);
}

