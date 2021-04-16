CC=gcc
CFLAGS= -Wall

all: main

%.o: %.c %.h
				$(CC)	$(CFLAGS)	-c	$^

main: node0.o node1.o node2.o node3.o prog3.c
				$(CC)	$(CFLAGS)	-o	$@ $^

clean: #make clean to return_number_at_po
			rm *.o *.h.gch main
