SRC=main3G.C image.C sink.C source.C PNMreader.C PNMwriter.C filters.C logging.C checksum.C color.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3G

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o proj3G proj3G_checksum output.pnm output.png
