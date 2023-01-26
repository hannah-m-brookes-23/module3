CFLAGS=-Wall -pedantic -std=c11 -I. -g

all:		test_list.bin

list.o: list.c list.h
	gcc $(CFLAGS) -c list.c

test_list.o: test_list.c list.h
	gcc $(CFLAGS) -c test_list.c

queue.o: queue.c queue.h
	gcc $(CFLAGS) -c queue.c

# .bin indicates binary file -> used for detection to run valgrind
test_list.bin:	test_list.o list.o
	gcc $(CFLAGS) test_list.o list.o -o test_list.bin

clean:
	rm -f *.o test_list.bin
