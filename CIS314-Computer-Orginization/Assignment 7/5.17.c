#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define VECTOR_SIZE 3 
typedef long long data_t; 
typedef data_t *vec_ptr;

data_t * get_vec_start(vec_ptr v) { 
	return v;
}

int vec_length(vec_ptr v) {
	return VECTOR_SIZE; 
}

void inner4(vec_ptr u, vec_ptr v, data_t *dest){
	
	long int i;
	int length = vec_length(u);
	data_t *udata = get_vec_start(u);
	data_t *vdata = get_vec_start(v);
	data_t sum = (data_t) 0;
	data_t sum2 = (data_t) 0;
	data_t sum3 = (data_t) 0;
	data_t sum4 = (data_t) 0;

	for (i=0; i < length; i+=4){
		sum += udata[i] * vdata[i];
		sum2 += udata[i+1] * vdata[i+2];
		sum3 += udata[i+2] * vdata[i+3];
		sum4 += udata[i+3] * vdata[i+4];
	}
	
	for (; i < length; i++){
		sum = sum + udata[i] * vdata[i];
	}

	*dest = sum + sum2 + sum3 +sum4;
}

int main(int argc, char const *argv[])
{
	int ms = 0;
	vec_ptr a= (vec_ptr) malloc(sizeof(data_t)*VECTOR_SIZE);
	// load values into a
	data_t ret=0;
	struct timeval start;
	gettimeofday(&start, NULL);
	inner4(a , a, &ret);
	struct timeval current;
	gettimeofday(&current, NULL);

	long long elapsed = (current.tv_sec - start.tv_sec)*1000000LL + (current.tv_usec - start.tv_usec);
	printf("%f Seconds\n", elapsed/1000000.0);

	return 0;
}

