FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format 
all: a.out
a.out: tree.o main.o a01.o a02.o a03.o a04.o a05.o a06.o a07.o
	g++ -static tree.o main.o a01.o a02.o a03.o a04.o a05.o a06.o a07.o -lm -o a.out
tree.o:
	g++ -c $(FLAGS) -o tree.o tree.cpp
main.o:
	g++ -c $(FLAGS) -o main.o main.cpp
a01.o:
	g++ -c $(FLAGS) -o a01.o task01.cpp
a02.o:
	g++ -c $(FLAGS) -o a02.o task02.cpp
a03.o:
	g++ -c $(FLAGS) -o a03.o task03.cpp
a04.o:
	g++ -c $(FLAGS) -o a04.o task04.cpp
a05.o:
	g++ -c $(FLAGS) -o a05.o task05.cpp
a06.o:
	g++ -c $(FLAGS) -o a06.o task06.cpp
a07.o:
	g++ -c $(FLAGS) -o a07.o task07.cpp
clean:
	rm -f *.o *.out
