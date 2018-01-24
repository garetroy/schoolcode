#include <stdio.h>
#define M 4

typedef int Marray_t[4][4];

void display(Marray_t Array){
    for(int i=0; i < M; i++){
        for (int j=0; j < 4; j++){
            printf("%x\n", Array[i][j]);
        }
    }
}

void transpose(Marray_t Array) {
    int i, j;
    int *x = Array[0];
    for (i = 0; i < M; i++){
    	int *p = &Array[0][i];
        for (j = 0; j < i; j++) {
            int t = x[j];
            x[j] = *p;
            *p = t;
            p += M;
	   } 
	x += M;
    }
}

int main (){

    Marray_t Array = {{5,6,7,8}, {9,10,11,12}, {13,14,15,16}, {17,18,19,20}};
    transpose(Array);
    display(Array);
    printf("\n--------NEXT SET----------\n\n");
    Marray_t Array2 = {{9,6,11,8}, {15,10,17,13}, {12,14,2,3}, {7,8,10,9}};
    transpose(Array2);
    display(Array2);
    return 0;
}