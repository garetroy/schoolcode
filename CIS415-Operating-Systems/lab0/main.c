#include <stdlib.h>
#include <stdio.h>

#include "iterator.h"
#include "treeset.h"


static int compare(void * i1, void * i2){
	int result, t1, t2;
	t1 = *(int*) i1;
	t2 = *(int*) i2;	
	if ( t1 == t2 ){
		result = 0;
	}else if ( t1 > t2 ){
		result = 1;
	}else{
		result = -1;
	}
	return result;	 
}

int main(){

	TreeSet * tree = ts_create(&compare);
	if( tree != NULL ){
		int i;
		int * t = NULL;
		for( i=0 ; i < 10 ; i++ ){
			t = (int*)(malloc(sizeof(int)));
			*t = i;
			ts_add(tree, t);
		}
		Iterator * it = ts_it_create(tree);
		if( it != NULL ) {
			void ** temp = (void**)malloc(sizeof(void*));
			for(; it_hasNext(it) ;){
				
				it_next(it,temp);
				printf("%d\n",*(int*)(*temp)); 
			}
		free(temp);
		it_destroy(it);
		}
	}
	return 0;
}
