FILE = reactor
OUT = a.out
TEST_FILE = $(FILE:=_test.cpp)
HDR = $(FILE:=.hpp) reactor_select.hpp server.hpp
OBJS = $(FILE:=.o)

CPPFLAGS := -Wall -ansi -pedantic-errors -Wextra -g -std=c++11
CC := g++ 

all: $(OUT)

$(OUT): $(TEST_FILE) $(HDR) server.cpp
	$(CC) $(CPPFLAGS) $< server.cpp -o $@

run: $(OUT)
	./$(OUT)

nm: $(OUT)
	nm -C > txt_nm
	code txt_nm

vlg: $(OUT)
	valgrind -v --leak-check=yes --track-origins=yes ./$(OUT)
C:
	cgdb ./$(OUT)

.PHONY: clean
clean:
	rm -f *.o

.PHONY: c
c:
	rm -f *.so* *.o *.out