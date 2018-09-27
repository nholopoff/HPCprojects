#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define COLUMN  10
#define MASTER  0

int main(){
	MPI_Init(NULL, NULL);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// make array
	int * array = malloc(COLUMN * sizeof(int));

	MPI_Barrier(MPI_COMM_WORLD);


	if (world_rank == MASTER){
		// fill array on head node only
		int i;
		for (i = 0; i < COLUMN; i++) 
			array[i] = i + 1;
		MPI_Barrier(MPI_COMM_WORLD);
		// head node sends out array with MPI_Bcast
		MPI_Bcast( &array, COLUMN, MPI_INT, MASTER, MPI_COMM_WORLD );
	}

	// return memory addresses
	MPI_Barrier(MPI_COMM_WORLD);
	
	printf("Node [%d] array[0] = %u\n", world_rank, &array[0]);
	/*
	if (world_rank == MASTER) {
		for (i = 0; i < COLUMN; i++)
			printf("Node [%d] array[%d] = %u", i, &array[i]);
	} else {
		for (i = 0; i < COLUMN; i++)
			//FIX ME
			printf("Node [%d] array[%d] = %u", world_rank, i, &array[i]); 
	}
	*/
	
	// Finalize MPI Environment
	MPI_Finalize();
}
