all: thv1 thv2 thv3 thv4

clean:
	rm thv1 thv2 thv3 thv4 thv1.o thv2.o thv3.o thv4.o p1fxns.o

thv1: thv1.o p1fxns.o
	cc -W -Wall -o thv1 thv1.o p1fxns.o

thv2: thv2.o p1fxns.o
	cc -W -Wall -o thv2 thv2.o p1fxns.o

thv3: thv3.o p1fxns.o
	cc -W -Wall -o thv3 thv3.o p1fxns.o

thv4: thv4.o p1fxns.o
	cc -g -W -Wall -o thv4 thv4.o p1fxns.o

thv1: thv1.c p1fxns.c p1fxns.h
thv2: thv2.c p1fxns.c p1fxns.h
thv3: thv3.c p1fxns.c p1fxns.h
thv4: thv4.c p1fxns.c p1fxns.h
p1fxns.o: p1fxns.c p1fxns.h
	gcc -c p1fxns.c
