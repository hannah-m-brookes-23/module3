
CFLAGS=-Wall -pedantic -std=c11 -L. -g

list.o:				list.c list.h
							gcc $(CFLAGS) -c list.c

