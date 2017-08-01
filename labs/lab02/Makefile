# COMP1927 15s2 Week 03 Lab

CC=gcc
CFLAGS=-Wall -Werror -g
BINS=testL myed

all: $(BINS)

testL : testList.o DLList.o
	$(CC) -o testL testList.o DLList.o

myed : myed.o DLList.o
	$(CC) -o myed myed.o DLList.o

DLList.o : DLList.c DLList.h

myed.o : myed.c DLList.h

testList.o : testList.c DLList.h

clean:
	rm -f $(BINS) *.o core
