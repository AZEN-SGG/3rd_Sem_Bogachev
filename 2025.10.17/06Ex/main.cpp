#include "solve.h"
#include "list.h"
#include "io_status.h"

#include <cstdio>
#include <ctime>
#include <new>
#include <exception>

int main(int argc, char *argv[])
{
	/* ./a06.out p filename */
	int p, res, task = 6;
	io_status ret;
	list_node *list = nullptr;
	double t;

	if (
		!(argc == 3
		&& sscanf(argv[1], "%d", &p) == 1)
	) {
		printf("Usage %s p filename\n", argv[0]);
		return 1;
	}

	ret = read_file(argv[2], &list);

	do {
		switch (ret)
		{
			case io_status::success:
				continue;
			case io_status::open:
				fprintf (stderr, "Cannot open %s\n", argv[2]);
				break;
			case io_status::format:
				fprintf (stderr, "Wrong format of file %s\n", argv[2]);
				break;
			case io_status::eof:
				fprintf (stderr, "End of file %s\n", argv[2]);
				break;
			case io_status::memory:
				fprintf (stderr, "Memory error\n");
				break;
		}
			
		return 3;
	} while (0);

	printf ("List:\n");
	print_list(list, p);

	t = clock();
	res = t6_solve(list);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
	
	delete_list(list);

	return 0;
}
