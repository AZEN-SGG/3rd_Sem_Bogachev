#include "solve.h"

void t9_solve (data *a, int n)
{
	while (n > 1)
	{
		int is_edge = 0, ind_x = findIndex(a, n, n >> 1);
		if (ind_x < n-ind_x)
		{
			if (ind_x == 0) is_edge = !ind_x;
			t9_solve(a, ind_x);
			a += ind_x + is_edge;
			n -= ind_x + is_edge;
		} else 
		{
			t9_solve(a+ind_x, n-ind_x);
			n = ind_x;
		}
	}
}

int findIndex (data *arr, int n, int m) 
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
