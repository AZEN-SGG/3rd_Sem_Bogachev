#include "solve.h"

void t8_solve(student *a, student *b, int n)
{
	int i = 2, hf_i = 1, j, margin;
	do {
		for (j = 0; j < n; j += i)
		{
			if (n < j+i)
			{
				margin = n-(j+hf_i);
				if (margin <= 0) 
					break;
			} else 
				margin = hf_i;

			unite(a+j, a+(j+hf_i), b, hf_i, margin);
			for (int k = 0; k < hf_i+margin; k++) 
				a[j+k] = (student&&)b[k];
		}
		
		hf_i = i;
		i <<= 1;
	} while (hf_i < n);
}

void unite(student *arr_a, student *arr_b, student *arr_c, int n, int m)
{
	int i, j, k, len = n + m;
	for (i=j=k=0; k < len; ++k)
	{
		if (i >= n)
   			arr_c[k] = (student&&)arr_b[j++];
  		else if (j >= m)
			arr_c[k] = (student&&)arr_a[i++];
  		else {
			if (arr_a[i] <= arr_b[j]) arr_c[k] = (student&&)arr_a[i++];
			else arr_c[k] = (student&&)arr_b[j++];
		} 
	}
}

