#include "solve_09.h"

int t9_solve(student *arr, int n, student& x)
{
	int len_del = 0,
	    last_to = 0,
	    last_l = 0,
	    l_less = 0,
	    r_less = 0;
	
	if (n > 1)
		len_del = last_to = last_l = (arr[1] < x);

	l_less = (arr[0] < x);

	for (int i = 1; i < n - 1; ++i)
	{
		r_less = (arr[i + 1] < x);
		if (l_less || r_less) {
			len_del++;
		} else {
			arr[i - len_del] = (student&&)arr[i];
		}

		l_less = last_l;
		last_l = r_less;
	}
	
	if (n > 1) {
		if (l_less)
			len_del++;
		else
			arr[n - 1 - len_del] = (student&&)arr[n - 1];
	}

	return n - len_del;
}

