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
	/* ./a08.out n p s [filename] */
	int n, p, s, diff, task = 8;
	data *arr_a, *arr_b;
	double t;

	arr_a=arr_b=nullptr;

	if (
		!((argc == 4 || argc == 5)
		&& sscanf(argv[1], "%d", &n) == 1 && n > 0 
		&& sscanf(argv[2], "%d", &p) == 1 
		&& sscanf(argv[3], "%d", &s) == 1 
		&& (((s == 0) && (argc == 5))
		|| ((s > 0) && (s < 5))))
	) {
		printf("Usage %s n p s name\n", argv[0]);
		return 1;
	}

	data::set_p(p);
	
	try	{ arr_a = new data[n]; }
	catch (const std::bad_alloc& e) {
		fprintf (stderr, "Not enough memory!\n");
		return 2;
	}

	try	{ arr_b = new data[n]; }
	catch (const std::bad_alloc& e) {
		delete[] arr_a;

		fprintf (stderr, "Not enough memory!\n");
		return 2;
	}

	if (s == 0) {
		char *name = argv[4];
		io_status ret = read_array(arr_a, n, name);
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
			
			delete[] arr_a;
			delete[] arr_b;

			return 3;
		} while (0);
	} else
		for (int i = 0; i < n; ++i)
			arr_a[i].init(s, n, i);

	printf ("Source array:\n");
	print_array(arr_a, n, p);

	t = clock();
	t8_solve(arr_a, arr_b, n);
	t = (clock() - t) / CLOCKS_PER_SEC;
	
	diff = diff_array(arr_a, n);

	printf ("New array:\n");
	print_array(arr_a, n, p);

	printf("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
	
	delete[] arr_a;
	delete[] arr_b;

	return 0;
}
