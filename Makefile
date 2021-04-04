CC=gcc
CFLAGS=-I.

calc: calc.o
	$(CC) -o calc calc.o 
clean:
	rm *.o calc
