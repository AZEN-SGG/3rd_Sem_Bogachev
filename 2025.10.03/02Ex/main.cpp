#include "solve.h"
#include "student.h"
#include "array.h"

#include <cstdio>
#include <ctime>
#include <new>
#include <exception>


int main(int argc, char *argv[])
{
	/* ./a02.out n p_a s_a [filename_a] m p_b s_b [filename_b] */
	int 	n, p_a, s_a, diff = 0,
		m, p_b, s_b, task = 2;
	student *arr_a, *arr_b, *arr_c;
	double t;

	arr_a=arr_b=arr_c=0;

	if (
		!((7 <= argc && argc <= 9)
		&& sscanf(argv[1], "%d", &n) == 1 && n > 0
		&& sscanf(argv[2], "%d", &p_a) == 1 
		&& sscanf(argv[3], "%d", &s_a) == 1 
		&& sscanf(argv[4+!s_a], "%d", &m) == 1 && m > 0
		&& sscanf(argv[5+!s_a], "%d", &p_b) == 1 
		&& sscanf(argv[6+(!s_a)*(argc>=8)], "%d", &s_b) == 1 
		&& (((7 + !s_a + !s_b) == argc)
		&& ((s_a >= 0 && s_b >= 0) && (s_a < 5 && s_b < 5))))
	) {
		printf("Usage %s n p_a s_a name_a m p_b s_b name_b\n", argv[0]);
		return 1;
	}

	
	try	{ arr_a = new student[n]; }
	catch (const std::bad_alloc& e) {
		fprintf (stderr, "Not enough memory!\n");
		return 2;
	}

	try	{ arr_b = new student[m]; }
	catch (const std::bad_alloc& e) {
		fprintf (stderr, "Not enough memory!\n");
		delete[] arr_a;
		return 2;
	}

	try	{ arr_c = new student[n+m]; }
	catch (const std::bad_alloc& e) {
		fprintf (stderr, "Not enough memory!\n");
		delete[] arr_a;
		delete[] arr_b;
		return 2;
	}

	if (	init_students(arr_a, n, s_a, s_a ? nullptr : argv[4])
		|| init_students(arr_b, m, s_b, s_b ? nullptr : argv[6+!s_a+!s_b]) 
	) {
		delete[] arr_a;
		delete[] arr_b;
		delete[] arr_c;
		return 3;
	}

	printf ("Array A:\n");
	print_students(arr_a, n, p_a);

	printf ("Array B:\n");
	print_students(arr_b, m, p_b);

	t = clock();
	t2_solve(arr_a, arr_b, arr_c, n, m);
	t = (clock() - t) / CLOCKS_PER_SEC;
	
	diff = diff_array(arr_c, n+m);

	printf ("New array:\n");
	print_students(arr_c, n+m, p_a + p_b);

	printf("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
	
	delete[] arr_a;
	delete[] arr_b;
	delete[] arr_c;

	return 0;
}
