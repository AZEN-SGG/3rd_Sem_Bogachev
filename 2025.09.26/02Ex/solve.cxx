#include "solve.h"


void t2_solve(data *arr_a, data *arr_b, data *arr_c, int n, int m)
{
	int i, j, k, len = n + m;
	for (i=j=k=0; k < len; ++k)
	{
		if (i >= n)
   			arr_c[k] = arr_b[j++];
  		else if (j >= m)
			arr_c[k] = arr_a[i++];
  		else {
			if (arr_a[i] <= arr_b[j]) arr_c[k] = arr_a[i++];
			else arr_c[k] = arr_b[j++];
		} 
	}
}

