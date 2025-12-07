#include "launch.h"

template <typename T>
int launch (char * path, char * filename, const int k, int r)
{
	rb_tree<T> *olha = new rb_tree<T>;
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
			case io_status::create:
				fprintf (stderr, "Error: Create, how is it possible?!\n"); // it is impossible...
				break;
		}

		delete olha;

		return 3;
	} while (0);

	fprintf (stdout, "Original tree:\n");
	olha->print(r);

    int (rb_tree<T>::*solves[])(const int) const = {
        &rb_tree<T>::t1_solve,
        &rb_tree<T>::t2_solve,
        &rb_tree<T>::t3_solve,
        &rb_tree<T>::t4_solve,
    };
    int len = sizeof(solves) / sizeof(solves[0]);

	double t = 0;
    int res = 0;
    for (int i = 0 ; i < len ; ++i)
    {
	    t = clock();
        res = (olha->*solves[i])(k);
        t = (clock() - t) / CLOCKS_PER_SEC;

	    fprintf(stdout, "%s : Task = %d K = %d Result = %d Elapsed = %.2f\n", path, i + 1, k, res, t);
    }

	delete olha;

	return 0;
}

template int launch<student>(char *, char *, int, int);

