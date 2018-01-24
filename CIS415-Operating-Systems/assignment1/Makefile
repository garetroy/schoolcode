CFLAGS=-W -Wall

all: finddupl

clean:
	rm -f *.o finddupl.o finddupl

finddupl: finddupl.o mentry.o mlist.o
	cc -o finddupl finddupl.o mentry.o mlist.o

finddupl.o: finddupl.c mentry.h mlist.h
mentry.o: mentry.h mentry.c
mlist.o: mlist.c mlist.h mentry.h
	gcc -g -c -W -Wall mlist.c
