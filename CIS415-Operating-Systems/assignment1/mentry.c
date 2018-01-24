#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mentry.h"

#define MAX_LEN 1024
/* This is my own work, except for the various articles that I pulled from online

fgets - https://linux.die.net/man/3/fgets
sscanf - https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
http://stackoverflow.com/questions/14099473/how-to-scanf-only-integer-and-repeat-reading-if-the-user-enter-non-numeric-chara

*/
MEntry *me_get(FILE*fd){
	if(fd == NULL)
		return NULL;
	MEntry (*entry) = (MEntry *)malloc(sizeof(MEntry));
	if(entry == NULL)return NULL;	

	(*entry).surname = (char *)malloc(sizeof(char)*MAX_LEN);
	if((*entry).surname == NULL)return NULL;

	(*entry).zipcode = (char *)malloc(sizeof(char)*MAX_LEN);
	if((*entry).zipcode == NULL)return NULL;

	(*entry).full_address = (char *)malloc(sizeof(char)*MAX_LEN);
	if((*entry).full_address == NULL)return NULL;
	memset((*entry).full_address, 0, MAX_LEN * sizeof(char));

	char buf[MAX_LEN];
	int count = 0;

	while(!feof(fd) && count < 3){
		memset(buf, 0, MAX_LEN * sizeof(char));
		if(fgets(buf,MAX_LEN,fd) == NULL){
			me_destroy(entry);
                        return NULL;
		}
		switch(count){
			case 0:
				sscanf(buf, "%[^,],", (*entry).surname);
				break;
			case 1:
				
				if(!sscanf(buf, "%d *s", &(*entry).house_number))
					(*entry).house_number = 0;
				break;
			case 2:
				sscanf(buf, "%*[^0-9]%s", (*entry).zipcode);
				break;
		}
		if(strcat((*entry).full_address,buf) == NULL) return NULL;
		count++;
		
	}
	return entry;
}

unsigned long me_hash(MEntry *me, unsigned long size){
	unsigned long hashval = 0;
	char *temp;

	for(temp = (*me).surname; *temp != '\0'; (temp)++)
		hashval = *temp + 31 * hashval; 

	for(temp = (*me).zipcode; *temp != '\0'; temp++)
		hashval = *temp + 31 * hashval;

	hashval = (*me).house_number + 31 * hashval;

	return hashval % size;	
}


void me_print(MEntry *me, FILE *fd){
	fprintf(fd, "%s", (*me).full_address);
	return;

}


int me_compare(MEntry *me1, MEntry *me2){
	int n = 0;
	n = (strcasecmp((*me1).surname,(*me2).surname) == 0 ? n : -1); 
	n = ((*me1).house_number == (*me2).house_number ? n : -1);
	n = (strcasecmp((*me1).zipcode, (*me2).zipcode) == 0 ? n : -1);
	return n;
}

void me_destroy(MEntry *me){
	free((*me).surname);
	free((*me).zipcode);
	free((*me).full_address);
	free(me);
	return;
}
