#include<mpi.h>
#include<stdio.h>

void main() {
	int world_rank, world_size, num1, num2;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	if (world_rank == 0) {
		scanf("%d", &num1);
		printf("Master sends %d \n", num1);
		MPI_Send(&num1,1,MPI_INT,1,1,MPI_COMM_WORLD);
	}

	else if (world_rank == 1) {
		MPI_Recv(&num2, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%d received by slave \n", num2);
	}

	MPI_Finalize();
}
