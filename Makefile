# this is the Makefile
CFLAGS=-Wall -pedantic -std=c11 -I.-g

all:		test1

list.o:	list.o list.h
	gcc $(CFLAGS) -c list.c

test1.o: test1.c list.h
	gcc $(CFLAGS) -c test1.c

test1: test1.o list.o
	gcc $(CFLAGS) test1.o list.o -o test1

clean:
	rm -f *.o test1
