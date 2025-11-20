CXX = g++
CXXFLAGS = -std=c++17 -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra \
           -Wunused -Wcast-align -Werror -pedantic -pedantic-errors \
           -Wfloat-equal -Wpointer-arith -Wformat-security \
           -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align \
           -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual \
           -Wno-suggest-attribute=format

SRCS = a01.cpp a02.cpp a03.cpp a04.cpp a05.cpp a06.cpp a07.cpp student.cpp solve.cpp
OBJS = $(SRCS:.cpp=.o)
TARGETS = a01.out a02.out a03.out a04.out a05.out a06.out a07.out

all: $(TARGETS)

%.out: %.o student.o solve.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS)

student.o: student.cpp student.h

solve.o: solve.cpp student.h
