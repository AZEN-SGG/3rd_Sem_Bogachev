#include "list.h"
#include "io_status.h"

#include <cstdio>
#include <ctime>
#include <new>
#include <exception>

int main(int argc, char *argv[])
{
	/* ./a01.out r filename k*/
	int r, k, task = 1;
	unsigned len_old = 0, len_new = 0;
	io_status ret;
	double t;

	if (
		!(argc == 4
		&& sscanf(argv[1], "%d", &r) == 1
		&& sscanf(argv[3], "%d", &k) == 1)
	) {
		printf("Usage %s r filename k\n", argv[0]);
		return 1;
	}

	list2 *roll = new list2;
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

	len_old = roll->get_length();

	printf ("Source list:\n");
	roll->print(r);

	t = clock();
	roll->shift(k);
	t = (clock() - t) / CLOCKS_PER_SEC;

	len_new = roll->get_length();

	printf ("New list:\n");
	roll->print(r);

	fprintf(stdout, "%s : Task = %d Len Old = %u Len New = %u Elapsed = %.2f\n", argv[0], task, len_old, len_new, t);
		
	delete roll;

	return 0;
}
