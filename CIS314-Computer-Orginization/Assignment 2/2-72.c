#include <stdio.h>
#include <string.h>
/*
	A:
	The if statement never fails becuase it is subtracting
	and int from an unsigned number, which is an unsigned value.
	This in turn is never less than 0.
*/

int copy_int(int val, void *buf, int maxbytes) {
	if (maxbytes >= sizeof(val)){
		memcpy(buf, (void *) &val, sizeof(val));
		return 1;
	}
	return 0;
} 

int main(){

	char buf[100];
    printf("Should be 1(maxbytes=16): %d\n", copy_int(0xDEADBEEF, buf, 16));
    printf("Should be 1(maxbytes=8): %d\n", copy_int(0xDEADBEEF, buf, 8));
    printf("Should be 1(maxbytes=4): %d\n", copy_int(0xDEADBEEF, buf, 4));
    printf("Should be 0(maxbytes=2): %d\n", copy_int(0xDEADBEEF, buf, 2));
    return 0;


}