#include <stdio.h>

int shift_two(int x, int y){

	/*
		This takes two input, x and y, which are both integers.
		Then it creates an int combined_number to where we are going to
		place the the intergers when they are combined. We then get the 
		last two digits of the integer y, but "Falsing" the statement everywhere
		except the last two digits.
		Then we do the reverse to x.
		We then "Or" them together (which will work because they are empty digits
		where we need to place them)
		then returns combined number
	*/
	int combined_number;
	y = (y & 0x000000FF);
	x = (x & 0xFFFFFF00);
	combined_number = (y | x);
	return combined_number;

}


int main(){

	printf("Should be: 0x89abcd10 Result: 0x%x\n", shift_two(0x89ABCDEF, 0x76543210));
	printf("Should be: 0xc1928392 Result: 0x%x\n", shift_two(0xC1928301, 0xF2349992));
	printf("Should be: 0x12394991 Result: 0x%x\n", shift_two(0x12394994, 0x10231991));
	printf("Should be: 0xfabbc292 Result: 0x%x\n", shift_two(0xFABBC292, 0xF2349992));

	return 0;

}