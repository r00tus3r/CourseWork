#include<mpi.h>
#include<stdio.h>

void main() {
	int world_rank, world_size, inp;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	if (world_rank == 0) {
		scanf("%d", &inp);
		printf("Root node sends %d to all others \n", inp);
	}

	MPI_Bcast(&inp, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("%d is received by process %d \n", inp, world_rank);
	MPI_Finalize();
}
