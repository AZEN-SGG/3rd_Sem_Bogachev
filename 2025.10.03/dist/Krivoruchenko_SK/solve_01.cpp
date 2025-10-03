#include "solve_01.h"

int t1_solve(student *a, int n, student& x)
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

