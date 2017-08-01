# Makefile for Generic List Iterator

CC = gcc
CFLAGS = -Wall -Werror -g

all : testListIteratorG

testListIteratorG : testListIteratorG.o listIteratorG.o  positiveIntType.o stringType.o 
	$(CC) -o testListIteratorG testListIteratorG.o listIteratorG.o positiveIntType.o stringType.o 

testListIteratorG.o : testListIteratorG.c listIteratorG.h positiveIntType.h stringType.h
	$(CC) $(CFLAGS) -c testListIteratorG.c

listIteratorG.o : listIteratorG.c listIteratorG.h  

positiveIntType.o : positiveIntType.c positiveIntType.h 
 
stringType.o : stringType.c stringType.h 



clean :
	rm -f *.o testListIteratorG core

