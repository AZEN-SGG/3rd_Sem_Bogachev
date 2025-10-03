#include "solve.h"

void t7_solve(student *arr, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int index = find(arr, i, arr[i]);
		if (index != i)
			append(arr, i+1, index);
	}
}

int find(student *a, int n, student& x)
{
	int avg = n >> 1,
	    answer = 0;
	
	while (n != 0)
	{
		if (x < a[avg])
			n = avg;
		else if (x > a[avg]) {
			answer += avg+1;
			a += avg+1;
			n -= avg+1;
		} else return answer + avg;

		avg = n >> 1;
	}

	return answer;
}

void append(student *arr, int n, int index)
{
	for (int i = n-1; i > index; --i)
		std::swap(arr[i], arr[i-1]);
}

