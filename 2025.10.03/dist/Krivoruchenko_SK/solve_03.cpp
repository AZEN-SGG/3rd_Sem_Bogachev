#include "solve_03.h"

int t3_solve(student *arr, int n, int m) 
{
	int i = 0, j = n-1;

	while (1) 
	{
		for (; i < n; i++) if (arr[i] >= arr[m]) break;
		for (; j >= 0; j--) if (arr[j] <= arr[m]) break;

		if (i == j) break;

		std::swap(arr[i], arr[j]);	
	
		if (i == m) {
			m = j;
			i++;
		} else if (j == m) {
			m = i;
			j--;
		} else
			i++, j--;
	}

	return i;
}
