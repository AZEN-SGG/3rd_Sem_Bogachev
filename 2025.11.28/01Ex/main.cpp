#include "student.h"
#include "list.h"
#include "tree.h"
#include "launch.h"

#include <cstdio>

template class list2_node<student>;
template class list2<student>;

template class tree_node<student>;
template class tree<student>;

template class tree_node< list2<student> >;
template class tree< list2<student> >;

template<>
int list2<student>::r = 0;
template<>
int list2<student>::m = 0;

int main(int argc, char *argv[])
{
	int r, m, res;

	if (
		!(argc == 4
		&& sscanf(argv[1], "%d", &r) == 1
		&& sscanf(argv[3], "%d", &m) == 1)
	) {
		printf("Usage %s r filename m\n", argv[0]);
		return 1;
	}

	res = launch<student>(argv[0], argv[2], r);
	if (res)
		return res;

	list2<student>::set_r(r);
	list2<student>::set_m(m);

	res = launch< list2<student> >(argv[0], argv[2], r);

	return res;
}
