#include "student.h"
#include "launch.h"

#include <cstdio>

int main(int argc, char *argv[])
{
	int r, k, res;

	if (
		!(argc == 4
		&& sscanf(argv[1], "%d", &r) == 1
		&& sscanf(argv[2], "%d", &k) == 1
	)) {
		printf("Usage %s r k filename\n", argv[0]);
		return 1;
	}

	res = launch<student>(argv[0], argv[3], k, r);

	return res;
}
