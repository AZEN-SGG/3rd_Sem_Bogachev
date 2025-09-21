#include "solve.h"
#include "sort.h"
#include "array.h"
#include "io_status.h"

#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	/* ./a01.out x_filename n p s [filename] */
	int n, p, res, task = 1;
	io_status ret;
	char *name, *x, **a;
	int (*cmp)(const char *, const char *);
	int (*f[])(const char *, const char *) = {up_strcmp, down_strcmp, up_len, down_len};
	int len_f = sizeof(f) / sizeof(f[0]);
	double t;

	if (
		!((argc == 5 || argc == 6)
		&& sscanf(argv[1], "%s", x_name) == 1
		&& sscanf(argv[2], "%d", &n) == 1 && n > 0 
		&& sscanf(argv[3], "%d", &p) == 1 
		&& sscanf(argv[4], "%d", &s) == 1 
		&& (((s == 0) && (sscanf(argv[5], "%s", filename) == 1))
		|| ((s > 0) && (s < 5))))
	) {
		printf("Usage %s x c n p name\n", argv[0]);
		return 1;
	}
	x = argv[1];
	name = argv[5];
	cmp = f[c-1];

	if (!(a = (char **)malloc(n * sizeof(char *))))
	{
		printf("Not enough memory: \n");
		return 2;
	}
	ret = read_array(a, n, name);

	do {
		switch(ret)
		{
			case SUCCESS:
				continue;
			case ERROR_OPEN:
				fprintf (stderr, "Cannot open %s\n", name);
				break;
			case ERROR_READ:
				fprintf (stderr, "Cannot read %s\n", name);
				break;
			case ERROR_MEM:
				fprintf (stderr, "Not enough memory");
				break;
		}

		delete[] a;
		return 3;
	} while (0);
	
	print_array(a, n, p);
	t = clock();
	res = t1_solve(a, n, x, cmp);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("%s : Task = %d Res = %d Elapsed = %.2f\n", argv[0], task, res, t);
	
	delete[] arr;

	return 0;
}
