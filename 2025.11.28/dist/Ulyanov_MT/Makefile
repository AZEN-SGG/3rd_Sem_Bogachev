FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format 
all: a.out
a.out: main.o
	g++ -static main.o -lm -o a.out
main.o:
	g++ -c $(FLAGS) -o main.o main.cpp
clean:
	rm -f *.o *.out
