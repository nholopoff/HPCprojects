
/* TODO
 * refactor code
 * add shuffle function instead of remaking path array each run
 * add function for storing best path array
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

/* constants */
static int const CITIES = 10;
static int const STEPS = CITIES;
static int const MAXRUNS = 10;

/* prototypes */
void GenerateDistance(int arr[CITIES][CITIES]);
void GeneratePath(int arr[STEPS]);
bool IsValueNotInArray(int val, int arr[STEPS]);
int GuessCheck(int pathArr[STEPS], int distArr[CITIES][CITIES]);
void InitializeArray(int arr[STEPS]);
void CopyPath(int _arr[STEPS], int arr[STEPS]);
void PrintBestPath(int arr[STEPS], int path);

/* function for generating distance matrix */
void GenerateDistance(int arr[CITIES][CITIES]) {
	int x, y;
	printf("\n");
	if (arr) {
		for (x = 0; x < CITIES; x++) {
			for (y = 0; y < CITIES; y++)
				arr[x][y] = (x == y) ? 0 : (rand() % 50 + 1);
		}
	}

	printf("Distance Array\n");
	for (x = 0; x < CITIES; x++) {
		for (y = 0; y < CITIES; y++){
			printf("%d ", arr[x][y]);
		}
		printf("\n");
	}
		printf("\n");

}

/* function for generating path to take */
void GeneratePath(int arr[STEPS]) {
	int i, r;
	if (arr) { 
		for (i = 0; i < STEPS; i++) {
			while (true) {
				r = (rand() % STEPS);
				if(IsValueNotInArray(r, arr)) {
					arr[i] = r;
					break;
				}
			}
		}
	}

	for (i=0; i < STEPS; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

/* function for checking if path is available */
bool IsValueNotInArray(int val, int arr[STEPS]) {
	int i;
	for (i=0; i < STEPS; i++) {
		if (arr[i] == val) 
			return false;
	}
	return true;
}

void InitializeArray(int arr[STEPS]) {
	int i;
	for (i = 0; i < STEPS; i++)
		arr[i] = -1;
}

void CopyPath(int _arr[STEPS], int arr[STEPS]) {
	int i;
	for (i = 0; i < STEPS; i++){
		arr[i] = _arr[i];
	}
}

void PrintBestPath(int arr[STEPS], int path) {
	int i;
	printf("Best Path\n");
	for (i = 0; i < STEPS; i++)
		printf("%d ", arr[i]);
	printf("\n");
	printf("Distance: %d\n", path);
}

int GuessCheck(int pathArr[STEPS], int distArr[CITIES][CITIES]) {
	int i, r, currentCity, nextCity, totalDist; 
	int bestDist = 9999999; 
	int bestPathArr[STEPS];

	for (r = 0; r < MAXRUNS; r++) {
		printf("Run [%d]:\n", (r + 1));
		GeneratePath(pathArr);
		totalDist = 0;

		/* randomly choose initial location */
		currentCity = pathArr[0];
		/* run through each city */
		for (i = 0; i < STEPS; i++) {
			nextCity = pathArr[i];
			totalDist += distArr[currentCity][nextCity];
			printf("%d\n", totalDist);
			currentCity = nextCity;
		}
		/* go back home */
		nextCity = pathArr[0];
		totalDist += distArr[currentCity][nextCity];
		printf("%d\n\n", totalDist);
		
		if (totalDist < bestDist) { 
			bestDist = totalDist;
			CopyPath(pathArr, bestPathArr);
		}
	
		InitializeArray(pathArr);
	}
	
	PrintBestPath(bestPathArr, bestDist);
}

int main(int argc, char **argv) {
	/* arrays */
	int distArr[CITIES][CITIES];
	int pathArr[STEPS];

	/* initialize random seed */
	srand((unsigned)time(NULL));

	/* populate distArr */
	GenerateDistance(distArr);

	/* guess and check */
	GuessCheck(pathArr, distArr);
	return 0;
}
