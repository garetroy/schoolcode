#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <printf.h> 

int writeto(FILE  *input, FILE *output){
	int *buffer = malloc(5 * sizeof(int));

	if(buffer == NULL){
		printf("pointer buffer was NULL");
		return 0;
	}

    for(int i = 0; i < 5; i++){
        fread(buffer, sizeof(int), 5, input);
        for(int j = 0; j < 5; j++)
        {
            fprintf(output, "%d\n", buffer[j]);
        }
        fseek(input, 5*sizeof(int), SEEK_CUR); 
    }
	free(buffer);
	return 0;
}



int main(int argc, char *argv[]){
	FILE *input_binary = fopen(argv[1], "r");
	FILE *output_binary = fopen(argv[2], "w");
	/* This was for testing purposes
	fseek(input_binary, 0, SEEK_END);
	int buff_size = ftell(input_binary);
	rewind(input_binary);
	int *buffer = malloc(buff_size);
	fread(buffer, sizeof(int), buff_size, input_binary);
	char *charBuffer = malloc(buff_size);
	int i;
	for(i = 0; i < (sizeof(int) * 30); i++){
		sprintf(charBuffer, "%d", buffer[i]);
		printf("%s ", charBuffer);
		if(i%9 == 0 && i !=0){
			printf("\n");
		}
	}
	free(charBuffer);
	free(buffer);
	*/
	writeto(input_binary, output_binary);
	fclose(input_binary);
	fclose(output_binary);
	return 0;
	
}
