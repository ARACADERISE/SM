SRC_C = $(wildcard src/*.c)
COMPILE = gcc -Wall -o main.o main.c

.PHONY: run
.PHONY: clear


run:
	@${COMPILE} ${SRC_C} && ./main.o

clear:
	@rm *.o
