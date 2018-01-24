#include <stdio.h>
#include <stdlib.h>


void bubblesort(int *array, int array_length){

	int swap;
	for (int i = 0 ; i < ( array_length - 1 ); i++){
    	for (int j = 0 ; j < array_length - i - 1; j++){
    		if (array[j] > array[j+1]){
				swap = array[j];
				array[j]   = array[j+1];
				array[j+1] = swap;
      		}
    	}
  	}

}


int main(){

	printf("Input the integer array length:");
	int array_length;
	scanf("%d\n",&array_length);

	int *array = (int *) malloc(sizeof(int) * array_length);

	for(int i = 0; i < array_length; i++){

		scanf("%d",&array[i]);
	}

	bubblesort(array, array_length);
	for(int i = 0; i < array_length; i++){

		printf("%d,",array[i]);

	}
	printf("\n");
	free(array);
	printf("Memory Freed!\n");

}