#include "list.h"
#include "io_status.h"

#include <cstdio>
#include <ctime>
#include <new>
#include <exception>

int main(int argc, char *argv[])
{
	/* ./a01.out r filename*/
	int r, diff, task = 1;
	io_status ret;
	double t = 0;

	if (
		!(argc == 3
		&& sscanf(argv[1], "%d", &r) == 1)
	) {
		printf("Usage %s r filename\n", argv[0]);
		return 1;
	}

	list *roll = new list;
	ret = roll->read_file(argv[2]);

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

		delete roll;

		return 3;
	} while (0);

	printf ("Source list:\n");
	roll->print(r);

	t = clock();
	roll->bubble_sort();
	t = (clock() - t) / CLOCKS_PER_SEC;

    diff = roll->num_diff();

	printf ("New list:\n");
	roll->print(r);

	fprintf(stdout, "%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);
		
	delete roll;

	return 0;
}
