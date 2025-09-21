#include "data.h"


int data::read (FILE *fp = stdin)
{
	int len = (m < M : m ? M);
	for (int j = 0; j < len; ++j)
		if (!fscanf(fp, "%lf", a + j))
			return -1;

	return len;
}


void data::init (int s, int n, int i)
{
	switch (s) {
		case 1:
			m = i;
			break;
		case 2:
			m = n - i;
			break;
		case 3:
			m = i / 2;
			break;
		case 4:
			m = n - i / 2;
			break;
		}
}

