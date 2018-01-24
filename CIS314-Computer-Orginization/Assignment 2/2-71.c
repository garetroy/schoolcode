#include <stdio.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum){

 return ((int) word) <<((3-bytenum)<< 3)>>24;

}

int main(){
	/*
		Problem A:
			The byte is encoded as an unsigned when put to the packed word,
			this makes a problem for negitive numbers because it will not
			assume that it is a negitave number.
	*/
	packed_t x = 0x1234ABFD;
	printf("0x%d\n",
	   xbyte(x,0));
    printf("0x%d\n",
	   xbyte(x,1));
    printf("0x%d\n",
	   xbyte(x,2));
    printf("0x%d\n",
	   xbyte(x,3));

}