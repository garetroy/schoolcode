all:
	mkdir include
	cp math330.h include/
	mkdir lib
	gcc -I./include -c trig/*.c
	gcc -I./include -c exp/*.c
	mv *.o lib/	
	ar r library.a  lib/*.o
	mv library.a lib
	gcc -I./include -L./lib -o cli/cli cli/cli.c -lrary

clean:
	rm -rf lib include *.o ./cli/cli