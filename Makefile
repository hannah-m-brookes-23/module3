CFLAGS=-Wall -pedantic -std=c11 -I. -g

all:		test1.bin

list.o: list.c list.h
	gcc $(CFLAGS) -c list.c

queue.o: queue.c queue.h
	gcc $(CFLAGS) -c queue.c

test1.o: test1.c list.h
	gcc $(CFLAGS) -c test1.c

# .bin indicates binary file -> used for detection to run valgrind
test1.bin:	test1.o list.o
	gcc $(CFLAGS) test1.o list.o -o test1.bin

clean:
	rm -f *.o test1.bin
