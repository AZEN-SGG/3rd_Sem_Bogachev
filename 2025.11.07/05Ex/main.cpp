#include "tree.h"
#include "io_status.h"

#include <cstdio>
#include <ctime>
#include <new>
#include <exception>

int main(int argc, char *argv[])
{
	/* ./a05.out r filename */
	int r;
	io_status ret;
	double t = 0;

	if (
		!(argc == 3
		&& sscanf(argv[1], "%d", &r) == 1)
	) {
		printf("Usage %s r filename\n", argv[0]);
		return 1;
	}

	tree *olha = new tree;
    if (olha == nullptr)
    {
		fprintf (stderr, "Error: MEMORY -> tree is nullptr\n");
        return 2;
    }

	ret = olha->read_file(argv[2]);

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

		delete olha;

		return 3;
	} while (0);

	printf ("Source tree:\n");
	olha->print(r);

    int (tree::*solves[])() = {
        &tree::t1_solve,
        &tree::t2_solve,
        &tree::t3_solve,
        &tree::t4_solve,
        &tree::t5_solve,
    };
    int len = sizeof(solves) / sizeof(solves[0]);

    int res = 0;
    for (int i = 0 ; i < len ; ++i)
    {
	    t = clock();
        res = (olha->*solves[i])();
        t = (clock() - t) / CLOCKS_PER_SEC;

	    fprintf(stdout, "%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], i + 1, res, t);
    }

	printf ("New tree:\n");
	olha->print(r);
		
	delete olha;

	return 0;
}
