#include <stdio.h>

int any_odd_one(unsigned x){

	/*
		This function compares the unsigned x to the number 0x555555555555
		What this does is it creates the binary 010101010101....(cont.)
		Then it compares the digits to see if they are the same value (1 would appear)
		if it is 1, then it would return 1, else no bits are odd, so it will return 0.
	*/

	if ((x & 0x5555555555) != 0){
		return 1;
	}
	return 0;
}

int main(){

	printf("Should be 0: %x\n", any_odd_one(0x222222));
	printf("Should be 1: %x\n", any_odd_one(0x222122));
	printf("Should be 0: %x\n", any_odd_one(0x222222));
	printf("Should be 1: %x\n", any_odd_one(0x222322));

}