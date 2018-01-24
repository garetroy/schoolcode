all: pass_serial pass_omp pass_tbb pass_cilk

pass_omp: pass_omp.c 
	icc -std=c99 -fopenmp -O3 -o pass_omp pass_omp.c -lcrypto

pass_tbb: pass_tbb.c
	icpc -fPIC -I$(TBBROOT)/include -o pass_tbb pass_tbb.c -L$(TBBLIB) -ltbb -lcrypto	
	
pass_cilk: pass_cilk.c
	icc -std=c99 -lcilkrts -o pass_cilk pass_cilk.c -lcrypto

pass_serial: pass_serial.c
	icc -std=c99 -o pass_serial pass_serial.c -lcrypto

check_serial: pass_serial
	./pass_serial 1120bfa29a3a834428dc477b68e2c872

check_omp: pass_omp 
	./pass_omp 1120bfa29a3a834428dc477b68e2c872	

check_cilk: pass_cilk 
	./pass_cilk 1120bfa29a3a834428dc477b68e2c872

check_tbb: pass_tbb
	./pass_tbb 1120bfa29a3a834428dc477b68e2c872
	

clean:
	rm -f *.o pass_serial pass_omp pass_tbb pass_cilk
