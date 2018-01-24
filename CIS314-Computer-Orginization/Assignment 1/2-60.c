#include <stdio.h>

unsigned replace_byte(unsigned init_num, int shiftby, unsigned char shiftwith){

	/*
		This function takes in three inputs init_num, shiftby, and shiftwith.
		It puts init's adress into a unsigned char pointer, defined as shiftbyspot
		then, so long as shiftby is not 0, it goes to the spot in the pointer specified
		by shiftby, then replaces that spot with shiftwith.
		(if it is 0, then it just addes to end)
		then it returns the number with the newly replaced characters.
	*/

    unsigned char *shiftbyspot = (unsigned char*)&init_num; //Copies initnumber into a pointer
    if (shiftby != 0){
    	shiftbyspot[sizeof(int)-shiftby] = shiftwith; //Shifts the pointer by the shiftby and puts shiftwith in it
    } else {
    	shiftbyspot[shiftby] = shiftwith;
    }
    return init_num; //returns the new number

}

int main(){

	printf("Should be 0xab345678: 0x%x\n", replace_byte(0x12345678, 1, 0xAB));
	printf("Should be 0x12ab5678: 0x%x\n", replace_byte(0x12345678, 2, 0xAB));
	printf("Should be 0x123457ab: 0x%x\n", replace_byte(0x12345678, 0, 0xAB));
	printf("Should be 0xab34ab78: 0x%x\n", replace_byte(0x12345678, 3, 0xAB));

	return 0;
}