all: stencil_serial stencil_omp stencil_cilk

stencil_serial: stencil_serial.cpp
	icpc -std=c++11 -o stencil_serial stencil_serial.cpp -Wall -Wextra -lopencv_core -lopencv_highgui -lm -fopenmp

stencil_omp: stencil_omp.cpp
	icpc -std=c++11 -o stencil_omp stencil_omp.cpp -Wall -Wextra -lopencv_core -lopencv_highgui -lm -fopenmp 

stencil_cilk: stencil_cilk.cpp
	icpc -std=c++11 -o stencil_cilk stencil_cilk.cpp -Wall -Wextra -lopencv_core -lopencv_highgui -lm -fopenmp -lcilkrts

check_serial: stencil_serial
	@./stencil_serial image.jpg

check_openmp: stencil_omp
	@./stencil_omp image.jpg

check_cilk: stencil_cilk
	@./stencil_omp image.jpg

clean:
	rm -f *.o stencil_serial stencil_omp out.jpg

.PHONY: clean
