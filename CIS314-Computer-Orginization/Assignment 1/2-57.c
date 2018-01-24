#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
	/*
		All this does is take the byte start, takes the length
		Then for as long as the length is, it runs a for loop to
		print out the digits in order.
	*/
	printf("0x");
	for (int i = 0; i < len; i++){
		printf(" %.2X", start[i]);
	}
	printf("\n");
}

void show_short(int x){
	show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x){
	show_bytes((byte_pointer) &x, sizeof(long int));
}

void show_double(int x){
	show_bytes((byte_pointer) &x, sizeof(double));
}

int main(){

	printf("Integer 5 results\n");
	printf("Short: ");
	show_short(5);
	printf("Long: ");
	show_long(5);
	printf("Double: ");
	show_double(5);
	printf("\n");

	printf("Integer 50 results\n");
	printf("Short: ");
	show_short(50);
	printf("Long: ");
	show_long(50);
	printf("Double: ");
	show_double(50);
	printf("\n");

	printf("Integer 123 results\n");
	printf("Short: ");
	show_short(123);
	printf("Long: ");
	show_long(123);
	printf("Double: ");
	show_double(123);
	printf("\n");

	return 0;

}