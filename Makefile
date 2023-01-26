CFLAGS=-Wall -pedantic -std=c11 -I. -g

all:		test_list.bin test_queue.bin

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

# .bin indicates binary file -> used for detection to run valgrind
test_list.bin:	test_list.o list.o
	gcc $(CFLAGS) test_list.o list.o -o $@

test_queue.bin: test_queue.o queue.o
	gcc $(CFLAGS) test_queue.o queue.o -o $@

clean:
	rm -f *.o test_*.bin
