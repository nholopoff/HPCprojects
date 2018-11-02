
/* TODO
 * refactor code
 * add shuffle function instead of remaking path array each run
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* prototypes */
generatedistance(int *arr, int size);
generatepath(int *arr, int size);
isvalueinarray(int val, int *arr, int size);

/* function for generating distance matrix */
void generatedistance(int *arr, int size){
	int x, y;
	if (arr) {
		for (x = 0; x < size; x++)
			for (y = 0; y < size; y++)
				arr[x][y] = if (x == y) ? 0 : (rand() % 50 + 1);
	}
}

/* function for generating path to take */
void generatepath(int *arr, int size){
	int r;
	if (arr) { 
		for (x = 0; x < size; x++){
			while (true) {
				r = rand() % size;
				if(isvaluenotinarray(r, *arr, size)){
					arr[x] = r;
					break;
				}
			}
		}
	}
}

/* function for checking if path is available */
bool isvaluenotinarray(int val, int *arr, int size){
	int i;
	for (i=0; i < size; i++){
		if (arr[i] == val) 
			return false;
	}
	return true;
}



int main(int argc, char **argv){

	/* variables */
	static int const CITIES = 9;
	static int const MAXRUNS = 50;

	static int bestDist;

	/* make array */
	static int distArr[CITIES][CITIES];
	static int * pathArr = malloc(CITIES * sizeof(int));

	/* initialize random seed */
	srand((unsigned)time(NULL));

	/* populate distArr */
	generatedistance(*distArr, CITIES);

	/*** GUESS AND CHECK ***/
	unsigned int i, currentCity, nextCity, run, totalDist = 0;
	for (run = 0; run < MAXRUNS; run++) {
		generatepath(*pathArr, CITIES);
		
		/* choose initial location */
		// PICK BY SELECTING INDEX 0 OF pathArr
		currentCity = pathArr[0];
		// RUN THE ALGORITHM
		for (i = 0; i < CITIES; i++) {
			nextCity = pathArr[i];
			totalDist += distArr[currentCity][nextCity];
			currentCity = nextCity;
		}
		if (totalDist < bestDist) 
			bestDist = totalDist;
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	memset(pathArr, 0, sizeof(pathArr));
	}

	/* print out best path */


	free(pathArr);
	return(0);
}
