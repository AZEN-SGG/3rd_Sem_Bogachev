#include "solve_01.h"

int t1_solve(data *a, int n, data& x) {
	int avg = n * 0.5;

	if (!n) return 0;
	
	if (x < a[avg]) return t1_solve(a, avg, x);
	if (x > a[avg]) return avg+1 + t1_solve(a+avg+1, n-(avg+1), x);
	else return avg;
}

