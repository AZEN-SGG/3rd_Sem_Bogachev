#include "solve_02.h"


void t2_solve(student *arr_a, student *arr_b, student *arr_c, int n, int m)
{
	int i, j, k, len = n + m;
	for (i=j=k=0; k < len; ++k)
	{
		if (i >= n)
   			arr_c[k] = arr_b[j++];
  		else if (j >= m)
			arr_c[k] = arr_a[i++];
  		else {
			if (arr_a[i] > arr_b[j]) 
				arr_c[k] = arr_b[j++];
			else 
				arr_c[k] = arr_a[i++];
		} 
	}
}

