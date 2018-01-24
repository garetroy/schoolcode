#include <stdio.h>
#include <stdlib.h>
#include "mlist.h"

#define HASH_SIZE 20
/*
This is my own work except for the help with my implementation from 
Howard Lin, Jack Brockway, and Chris Brooks

I would like to state what functions they helped me with, but in reality they have helped with
all parts of my implementation of code as I have helped them.

*/

typedef struct entry Entry;

struct entry{
	unsigned long  key;
	MEntry *value;
	Entry *next;
};

typedef struct mlist{
	
	Entry **entry_table;
	unsigned long size;

}MList;

MList *ml_create(void){
	MList *_mlist;
	unsigned long  i;

	_mlist = (MList *) malloc(sizeof(MList));	
	if(_mlist == NULL)
		return NULL;

	(*_mlist).size = HASH_SIZE;

        (*_mlist).entry_table = (Entry **) malloc(sizeof(Entry *) * (*_mlist).size);
        if((*_mlist).entry_table == NULL)
              return NULL;
	
	for(i = 0; i < (*_mlist).size; i++)
		(*_mlist).entry_table[i] = NULL;

	return _mlist;

}


int ml_add(MList **ml, MEntry *me){
	Entry* _entry;
	Entry* _next;
	Entry* _last;
	unsigned long count;
	count = 0;

	if(ml_lookup(*ml, me) != NULL)
		return 1;

	_entry = (Entry *) malloc(sizeof(Entry));
	if(_entry == NULL)
		return 0;
	
	(*_entry).value = me;
	(*_entry).key = me_hash(me, (**ml).size);
	_next = (**ml).entry_table[(*_entry).key];
	
	if((**ml).entry_table[(*_entry).key] == NULL){
		(**ml).entry_table[(*_entry).key] = _entry;
		return 1;
	}
	
	while(_next != NULL){
		_last = _next;
		_next = (*_next).next;
		count++;
	}

	(*_last).next = _entry;

	if(count > (**ml).size){
		fprintf(stderr, "Size of Hash:%lu, Resizing Hash\n",(**ml).size);	
		unsigned long i;
		unsigned long old_size;
		Entry **curr_entrytable;
		Entry *curr_entry;
		Entry *_next;

		Entry **temp_entry = (Entry **)calloc(2 * (**ml).size, sizeof(Entry *));
		if(temp_entry == NULL)
			return 0;

		curr_entrytable = (**ml).entry_table;
		(**ml).entry_table = temp_entry;

		old_size = (**ml).size;
		(**ml).size = 2 * (**ml).size;
		

		for(i = 0; i < old_size; i++){
			if(curr_entrytable[i] != NULL && curr_entrytable[i]->value != NULL){
				curr_entry = curr_entrytable[i];
				while(curr_entry != NULL){	
					_next = (*curr_entry).next;
					if((*curr_entry).value != NULL)
						ml_add(ml, (*curr_entry).value);
				//	free(curr_entry);
					curr_entry = _next;
				}
			}	
		}	
	//		if(curr_entrytable != NULL)
	//			free(curr_entrytable); 
	}
	
	return 1;			       	
}

MEntry *ml_lookup(MList *ml, MEntry *me){
	unsigned  hash;
	Entry *_entry;	

	hash = me_hash(me,(*ml).size);
	for(_entry = (*ml).entry_table[hash]; _entry != NULL; _entry = (*_entry).next){
		if(me_compare((*_entry).value,me) == 0)
			return (*_entry).value;
	}
	return NULL;
}

void ml_destroy(MList *ml){
	Entry* _next;
	Entry *_last;
	unsigned long i;
	
	for(i = 0; (*ml).size >= i; i++){

		_next = (*ml).entry_table[i];
		while(_next != NULL){
			_last = _next;
			_next = (*_next).next;
		
			if(_last != NULL && (*_last).value != NULL)		
				me_destroy((*_last).value);
			free(_last);

		}
	}
	free(ml->entry_table);
	free(ml);
}
