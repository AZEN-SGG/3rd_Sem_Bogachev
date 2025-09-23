#include "solve.h"

void t7_solve(data *arr, int n)
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
	int avg = n * 0.5;

	if (!n) return 0;
	
	if (x < arr[avg]) return find(arr, avg, x);
	if (x > arr[avg]) return avg+1 + find(arr+avg+1, n-(avg+1), x);
	else return avg;
}

void append(data *arr, int n, data x, int index)
{
	for (int i = n-1; i > index; --i)
		arr[i] = arr[i-1];
	arr[index] = x;
}

