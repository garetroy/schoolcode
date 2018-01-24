SRC=main3E.C image.C sink.C source.C PNMreader.C PNMwriter.C filters.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ -g $(OBJ) -o proj3E

.C.o: $<
	g++ -g -I. -c $<

clean:
	rm *.o proj3E output.pnm output.png
