
all: crypto_serial crypto_omp crypto_tbb crypto_cilk

crypto_omp: omp.c key.c
	icc -std=c99 -fopenmp -O3 -o crypto_omp omp.c key.c

crypto_tbb: tbb.c key.c
	icpc -fPIC -I$(TBBROOT)/include -o crypto_tbb tbb.c -L$(TBBLIB) -ltbb 

crypto_cilk: cilk.c key.c
	icpc -lcilkrts -o crypto_serial serial.c key.c

crypto_serial: serial.c key.c
	icc -std=c99 -o crypto_serial serial.c key.c

check_serial: crypto_serial
	./crypto_serial superSecretText keys/key73 keys/key173 > cipher_serial &&\
	./crypto_serial cipher_serial   keys/key73 keys/key173

check_omp: crypto_omp
	./crypto_omp superSecretText keys/key73 keys/key173 > cipher_omp &&\
	./crypto_omp cipher_omp  keys/key73 keys/key173

check_tbb: crypto_tbb
	./crypto_tbb superSecretText keys/key73 keys/key173 > cipher_tbb &&\
	./crypto_tbb cipher_tbb  keys/key73 keys/key173

check_cilk: crypto_cilk
	./crypto_cilk superSecretText keys/key73 keys/key173 > cipher_cilk &&\
	./crypto_cilk cipher_cilk  keys/key73 keys/key173

clean:
	rm -f *.o crypto_serial crypto_omp crypto_tbb crypto_cilk cipher_serial
	
.PHONY:	clean
