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
	/* ./a01.out x_filename n p s [filename] */
	int n, p, s, res, task = 1;
	io_status ret;
	char *x_name;
	data *x = 0, *arr = 0;
	FILE *fp = 0;
	double t;

	if (
		!((argc == 5 || argc == 6)
		&& sscanf(argv[2], "%d", &n) == 1 && n > 0 
		&& sscanf(argv[3], "%d", &p) == 1 
		&& sscanf(argv[4], "%d", &s) == 1 
		&& (((s == 0) && (argc == 6))
		|| ((s > 0) && (s < 5))))
	) {
		printf("Usage %s x n p s name\n", argv[0]);
		return 1;
	}

	data::set_p(p);
	
	x_name = argv[1];
	if (!(fp = fopen(x_name, "r"))) {
		fprintf (stderr, "Cannot open %s\n", x_name);
		return 3;
	}

	try	{ x = new data(); }
	catch (const std::bad_alloc& e) {
		fprintf (stderr, "Not enough memory!\n");
		return 2;
	}

	if ((x->read(fp)) == -1) {
		fprintf (stderr, "Cannot read %s\n", x_name);
		delete x;
		fclose(fp);
		return 3;
	}

	fclose(fp);

	try	{ arr = new data[n]; }
	catch (const std::bad_alloc& e) {
		fprintf (stderr, "Not enough memory!\n");
		delete x;
		return 2;
	}

	if (s == 0) {
		char *name = argv[5];
		ret = read_array(arr, n, name);
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
			
			delete x;
			delete[] arr;

			return 3;
		} while (0);
	} else
		for (int i = 0; i < n; ++i)
			arr[i].init(s, n, i);

	printf ("X:\n");
	x->print();

	printf ("Source array:\n");
	print_array(arr, n, p);

	t = clock();
	res = t1_solve(arr, n, *x);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("%s : Task = %d Res = %d Elapsed = %.2f\n", argv[0], task, res, t);
	
	delete x;
	delete[] arr;

	return 0;
}
