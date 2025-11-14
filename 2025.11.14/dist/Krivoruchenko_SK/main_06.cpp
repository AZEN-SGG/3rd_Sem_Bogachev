#include "tree.h"
#include "io_status.h"

#include <cstdio>
#include <ctime>
#include <new>
#include <exception>

int main(int argc, char *argv[])
{
	/* ./a06.out r filename name value */
	int r, value, task = 6;
	io_status ret;
	double t = 0;

	if (
		!(argc == 5
		&& sscanf(argv[1], "%d", &r) == 1
        && sscanf(argv[4], "%d", &value) == 1)
	) {
		printf("Usage %s r filename name value\n", argv[0]);
		return 1;
	}

    student in(argv[3], value);

	tree olha;
	ret = olha.read_file(argv[2]);
	do {
		switch (ret)
		{
			case io_status::success:
				continue;
			case io_status::open:
				fprintf (stderr, "Error: Cannot open %s\n", argv[2]);
				break;
			case io_status::format:
				fprintf (stderr, "Error: Wrong format of file %s\n", argv[2]);
				break;
			case io_status::eof:
				fprintf (stderr, "Error: End of file %s\n", argv[2]);
				break;
			case io_status::memory:
				fprintf (stderr, "Error: MEMORY\n");
				break;
		}

		return 3;
	} while (0);

	printf ("Original tree:\n");
	olha.print(r);
	olha.print_stat(argv[0], task);
	
	t = clock();
	olha.t6_solve(in);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf ("Modified tree:\n");
	olha.print(r);
	olha.print_stat(argv[0], task, t);

	return 0;
}
