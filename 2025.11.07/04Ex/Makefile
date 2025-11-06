TASK ?= 04

WFLAGS = -O3 -mfpmath=sse -fstack-protector-all -g \
-W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors \
-Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute \
-Wformat=1 -Wwrite-strings -Wno-long-long -Woverloaded-virtual \
-Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -std=c++11

ifeq ($(OS),Windows_NT)
	EXE = exe
	CLEAN = del
else
	EXE = out
	CLEAN = rm -f
endif

TARGET = a$(TASK).$(EXE)
OBJ = main.o tree.o t1_solve.o t2_solve.o t3_solve.o t4_solve.o 

%.o: %.cpp
	g++ $(WFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	g++ $(WFLAGS) $^ -o $@

gdb: WFLAGS = -mfpmath=sse -fstack-protector-all -g -O0 -Wall -Wextra -Werror -std=c++11
gdb: clean $(TARGET)

prof: WFLAGS += -pg
prof: clean $(TARGET)

clean celan:
	$(CLEAN) *.o *.$(EXE)

