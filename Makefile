CFLAGS=-Wall -pedantic -std=c11 -I. -g

all:		test_list.bin test_queue.bin

list.o: list.c list.h
	gcc $(CFLAGS) -c list.c

queue.o: queue.c queue.h
	gcc $(CFLAGS) -c queue.c

test_list.o: test_list.c list.h
	gcc $(CFLAGS) -c test_list.c

test_queue.o: test_queue.c queue.h
	gcc $(CFLAGS) -c test_queue.c

# .bin indicates binary file -> used for detection to run valgrind
test_list.bin:	test_list.o list.o
	gcc $(CFLAGS) test_list.o list.o -o test_list.bin

test_queue.bin: test_queue.o queue.o
	gcc $(CFLAGS) test_queue.o queue.o -o test_queue.bin

clean:
	rm -f *.o test_*.bin
