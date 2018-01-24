SRC=main4C.C image.C sink.C source.C PNMreader.C PNMwriter.C filters.C logging.C checksum.C color.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj4C

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o proj4C checksum output.pnm output.png
