#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 10
#define COLUMN 10

int main(){
	int randMatrix[ROW][COLUMN];
	
	unsigned int x;
	unsigned int y;

	// make matrix (1 - 500)
	srand(time(NULL));
	for(x = 0; x < 10; x++){
		for(y = 0; y < 10; y++){
			randMatrix[x][y] = rand() % 500 + 1;
		}
	}
	puts("Matrix successfully created");

	// generate csv
	FILE *fp;

	fp = fopen("input.csv", "w");
	for(x = 0; x < 10; x++){
		for(y = 0; y < 10; y++){
			fprintf(fp, "%d,", randMatrix[x][y]);
		}
	}
	fclose(fp);
	return 0;
}
