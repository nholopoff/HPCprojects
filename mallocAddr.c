#include <stdio.h>
#include <stdlib.h>

int main(){
	int *iptr;

	iptr = (int *) malloc(4);
	printf("Address=%u\n", iptr);

	free(iptr);
	return 0;
}
