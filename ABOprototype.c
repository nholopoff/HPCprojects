#include <stdio.h>
#include <stdlib.h>

#define ROW 10
#define COLUMN 10

static unsigned int cityMatrix[ROW][COLUMN];

int main(){

	// initialize matrix with csv file
	FILE datafile*;

	datafile = fopen("input.csv", "r");
	if(!datafile){
		perror("No file!");
		return 1;
	}

	while( fscanf(datafile, "%d,", &num) > 0 )
	
	fclose(datafile);

	return 0;
}
