#include <stdio.h>

void decode2(int x, int y, int z){

	int edx, eax;

	edx = y; //movl 12(%edp), %edx
	printf("Set edx equal to y: %x\n", edx);
	edx = z - edx; //subl 16(%edp), %edx
	printf("Subtract z from edx: %x\n", edx);
	eax = edx; //movl %edx, %eax
	printf("Set eax equal to edx: %x\n", eax);
	eax = (eax << 31); //sall $31, %eax
	printf("Shift eax left by 31bits: %x\n", eax);
	eax = eax >> 31; //sarl $31, %eax
	printf("Shifts eax right by 31bits: %x\n", eax);
	edx = edx * x; //imull 8(%edp), %edx
	printf("Multiplys edx by x: %x\n", edx);
	eax = edx ^ eax; // xorl %edx, %eax
	printf("XOR edx and eax: %x\n", eax);

}

int main(){

	int x,y,z;
	x = 0x3;
	y = 0x02;
	z = 0x05;
	decode2(x,y,z);
	printf("Should be fffffff6\n");
	x = 0x1;
	y = 0x02;
	z = 0x03;
	decode2(x,y,z);
	printf("Should be fffffffe\n");
	
}