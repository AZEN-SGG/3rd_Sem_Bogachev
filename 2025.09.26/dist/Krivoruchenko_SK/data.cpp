#include "data.h"


int data::read (FILE *fp)
{
	if (fscanf(fp, "%d", &m) != 1) {
		return -1;
	}
	
	m = get_M();

	for (int j = 0; j < m; ++j)
		if (!fscanf(fp, "%lf", a + j))
			return -1;

	return m;
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

