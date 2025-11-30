#include "student.h"
#include "launch.h"

#include <cstdio>

int main(int argc, char *argv[])
{
	/* ./a01.out m r k filename */
	int m, r, k, res;

	if (
		!(argc == 5
		&& sscanf(argv[1], "%d", &m) == 1 && (m > 0)
		&& sscanf(argv[2], "%d", &r) == 1
		&& sscanf(argv[3], "%d", &k) == 1
	)) {
		printf("Usage %s m r k filename\n", argv[0]);
		return 1;
	}

	res = launch<student>(argv[0], argv[4], m, k, r);

	return res;
}
