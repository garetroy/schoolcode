CFLAGS=-W -Wall
OBJECTS=BoundedBuffer.o diagnostics.o freesectordescriptorstore.o \
        generic_queue.o sectordescriptor.o \
        sectordescriptorcreator.o testharness.o fakeapplications.o \
        diskdevice.o diskdriver.o p1fxns.o

my_demo: $(OBJECTS)
	cc -o my_demo $(OBJECTS) -lpthread

clean:
	rm -f *.o my_demo

diskdriver.o: diskdriver.h diskdriver.c
p1fxns.o: p1fxns.h p1fxns.c
