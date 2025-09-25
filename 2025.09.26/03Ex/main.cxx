#include "solve.h"
#include "data.h"
#include "array.h"
#include "io_status.h"

#include <stdio.h>
#include <time.h>
#include <new>
#include <exception>

int data::p = 0;

int main(int argc, char *argv[])
{
	/* ./a03.out m n p s [filename] */
	int m, n, p, s, res, task = 3;
	data *arr = 0;
	double t;

	if (
		!((argc == 5 || argc == 6)
		&& sscanf(argv[1], "%d", &m) == 1 
		&& sscanf(argv[2], "%d", &n) == 1 && n > 0 
		&& (0 <= m && m < n)
		&& sscanf(argv[3], "%d", &p) == 1 
		&& sscanf(argv[4], "%d", &s) == 1 
		&& (((s == 0) && (argc == 6))
		|| ((s > 0) && (s < 5))))
	) {
		printf("Usage %s m n p s name\n", argv[0]);
		return 1;
	}

	data::set_p(p);
	
	try	{ arr = new data[n]; }
	catch (const std::bad_alloc& e) {
		fprintf (stderr, "Not enough memory!\n");
		return 2;
	}

	if (s == 0) {
		char *name = argv[5];
		io_status ret = read_array(arr, n, name);
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
					fprintf (stderr, "Not enough memory\n");
					break;
			}
			
			delete[] arr;

			return 3;
		} while (0);
	} else
		for (int i = 1; i <= n; ++i)
			arr[i-1].init(s, n, i);

	printf ("Source array:\n");
	print_array(arr, n, p);

	t = clock();
	res = t3_solve(arr, n, m);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf ("New array:\n");
	print_array(arr, n, p);

	printf("%s : Task = %d Res = %d Elapsed = %.2f\n", argv[0], task, res, t);
	
	delete[] arr;

	return 0;
}
