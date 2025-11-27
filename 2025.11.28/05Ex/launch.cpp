#include "launch.h"

template <typename T>
int launch (char * path, char * filename, int r, int m)
{
	tree<T> *olha = new tree<T>;
    if (!olha)
    {
		fprintf (stderr, "Error: MEMORY -> tree is nullptr\n");
        return 2;
    }

	io_status ret = olha->read_file(filename);

	do {
		switch (ret)
		{
			case io_status::success:
				continue;
			case io_status::open:
				fprintf (stderr, "Error: Cannot open %s\n", filename);
				break;
			case io_status::format:
				fprintf (stderr, "Error: Wrong format of file %s\n", filename);
				break;
			case io_status::eof:
				fprintf (stderr, "Error: End of file %s\n", filename);
				break;
			case io_status::memory:
				fprintf (stderr, "Error: MEMORY\n");
				break;
		}

		delete olha;

		return 3;
	} while (0);

	fprintf (stdout, "Original tree:\n");
	olha->print(r);

    int (tree<T>::*solves[])() const = {
        &tree<T>::t1_solve,
        &tree<T>::t2_solve,
        &tree<T>::t3_solve,
        &tree<T>::t4_solve,
        &tree<T>::t5_solve,
    };
    int len = sizeof(solves) / sizeof(solves[0]);

	double t = 0;
    int res = 0;
    for (int i = 0 ; i < len ; ++i)
    {
	    t = clock();
        res = (olha->*solves[i])();
        t = (clock() - t) / CLOCKS_PER_SEC;

	    fprintf(stdout, "%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", path, i + 1, m, res, t);
    }

	fprintf (stdout, "Modified tree:\n");
	olha->print(r);
		
	delete olha;

	return 0;
}

template int launch<student>(char *, char *, int, int);
template int launch< list2<student> >(char *, char *, int, int);

