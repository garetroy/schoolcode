

# The first target in a makefile is the one which will be triggered if
# no explicit target is given, traditionaly this target is named "all".

all: matmul_serial matmul_omp matmul_cilk matmul_tbb

matmul_serial: matmul_serial.c
	icc -o matmul_serial matmul_serial.c -fopenmp

matmul_omp: matmul_omp.c
	icc -std=c99 -fopenmp -o matmul_omp matmul_omp.c 

matmul_cilk: matmul_cilk.c
	icpc -lcilkrts -fopenmp -o matmul_cilk matmul_cilk.c 

matmul_tbb:


check_serial: matmul_serial
	./matmul_serial 

check_omp: matmul_omp
	./matmul_omp

check_cilk: matmul_cilk
	./matmul_cilk

check_tbb: matmul_tbb
	matmul_tbb


clean:
	rm -f  matmul_serial matmul_omp matmul_cilk matmul_tbb *.o
