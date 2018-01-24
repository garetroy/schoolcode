#include <stdio.h>

typedef struct ELE *tree_ptr;

struct ELE {
  long val;
  tree_ptr left;
  tree_ptr right;
};

long trace(tree_ptr tp) {
	struct ELE* current = tp;
	if(!current) {
		return 0;
	}
	else{
    	while(temp) { //Checks to see if it is still something
      		temp = current->val
      		current = current->right;
    	}
    return current->val;
  	}
}


int main(){
	return 0;
}

/* This function goes through the tree nodes from the right, going to each node then it is done when
it compeletes going through all nodes