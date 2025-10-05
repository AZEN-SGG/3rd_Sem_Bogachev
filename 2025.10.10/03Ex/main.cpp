#include "solve.h"
#include "student.h"
#include "array.h"
#include "io_status.h"

#include <cstdio>
#include <ctime>
#include <new>
#include <exception>

int main(int argc, char *argv[])
{
	/* ./a03.out n p s [filename] */
	int n, p, s, res, task = 3;
	student *arr = 0;
	double t;

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

	try	{ arr = new student[n]; }
	catch (const std::bad_alloc& e) {
		fprintf (stderr, "Not enough memory!\n");
		return 2;
	}

	if (s == 0) {
		char *name = argv[4];
		io_status ret = read_students(arr, n, name);
		do {
			switch (ret)
			{
				case io_status::success:
					continue;
				case io_status::open:
					fprintf (stderr, "Cannot open %s\n", name);
					break;
				case io_status::format:
					fprintf (stderr, "Wrong format of file %s\n", name);
					break;
				case io_status::eof:
					fprintf (stderr, "End of file %s\n", name);
					break;
				case io_status::memory:
					fprintf (stderr, "Memory error\n");
					break;
			}
			
			delete[] arr;

			return 3;
		} while (0);
	} else
		for (int i = 0; i < n; ++i)
			arr[i].init_f(s, n, i+1);

	printf ("Source students:\n");
	print_students(arr, n, p);

	t = clock();
	res = t3_solve(arr, n);
	t = (clock() - t) / CLOCKS_PER_SEC;
	
	printf ("New students:\n");
	print_students(arr, res, p);

	printf("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
	
	delete[] arr;

	return 0;
}
