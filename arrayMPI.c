#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define COLUMN  10 // array size
#define MASTER  0 // Head node

int main(){
	MPI_Init(NULL, NULL);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// make linear array, allocate memory based on size
	int *array = malloc(COLUMN * sizeof(int));

	/* Synchronize, fill array on head node, then copy array values to all nodes */
	MPI_Barrier(MPI_COMM_WORLD);
	if (world_rank == MASTER){
		// fill array on head node only
		int i;
		for (i = 0; i < COLUMN; i++) 
			array[i] = i + 1;
		MPI_Barrier(MPI_COMM_WORLD);
		/* head node sends out array with MPI_Bcast
		MPI_Bcast essentially combines a send/recv into a single function call
		It also incorporates a tree data structure, greatly improving network speed
*/		
		MPI_Bcast( &array, COLUMN, MPI_INT, MASTER, MPI_COMM_WORLD );
	}

	// return memory addresses from index 0
	MPI_Barrier(MPI_COMM_WORLD);
	printf("Node [%d] array[0] = %u\n", world_rank, &array[0]);
	
	// Finalize MPI Environment, no return statement necessary
	MPI_Finalize();
}
