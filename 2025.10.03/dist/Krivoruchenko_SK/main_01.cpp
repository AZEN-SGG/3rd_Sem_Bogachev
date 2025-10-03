#include "solve_01.h"
#include "student.h"
#include "array.h"
#include "io_status.h"

#include <cstdio>
#include <ctime>
#include <new>
#include <exception>

int main(int argc, char *argv[])
{
	/* ./a01.out name age n p s [filename] */
	int age, n, p, s, res, task = 1;
	io_status ret;
	student *x = nullptr, *arr = nullptr;
	double t;

	if (
		!((argc == 6 || argc == 7)
		&& sscanf(argv[2], "%d", &age) == 1
		&& sscanf(argv[3], "%d", &n) == 1 && n > 0 
		&& sscanf(argv[4], "%d", &p) == 1
		&& sscanf(argv[5], "%d", &s) == 1
		&& (((s == 0) && (argc == 7))
		|| ((s > 0) && (s < 5))))
	) {
		printf("Usage %s name age n p s filename\n", argv[0]);
		return 1;
	}

	try	{ x = new student(argv[1], age); }
	catch (const std::bad_alloc& e) {
		fprintf (stderr, "Not enough memory!\n");
		return 2;
	}

	try	{ arr = new student[n]; }
	catch (const std::bad_alloc& e) {
		fprintf (stderr, "Not enough memory!\n");
		delete x;
		return 2;
	}

	if (s == 0) {
		char *name = argv[6];
		ret = read_students(arr, n, name);
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
			
			delete x;
			delete[] arr;

			return 3;
		} while (0);
	} else
		for (int i = 0; i < n; ++i)
			arr[i].init_f(s, n, i+1);

	printf ("X:\n");
	x->print();

	printf ("Source students:\n");
	print_students(arr, n, p);

	t = clock();
	res = t1_solve(arr, n, *x);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("%s : Task = %d Res = %d Elapsed = %.2f\n", argv[0], task, res, t);
	
	delete x;
	delete[] arr;

	return 0;
}
