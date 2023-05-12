#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]) {
	int rank,size,num;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	if (rank == 0) {
		printf("Enter a number: ");
		fflush(stdout);
		scanf_s("%d", &num);
		int dest = (rank + 1) % size;
		num++;
		MPI_Send(&num, 1, MPI_INT, dest, dest, MPI_COMM_WORLD);
		fprintf(stdout, "Number: %d sent from process %d to  process %d\n", num, rank, dest);
		fflush(stdout);

		int src = size-1;
		MPI_Recv(&num, 1, MPI_INT, src, rank, MPI_COMM_WORLD, &status);
		fprintf(stdout, "Number: %d received in process %d\n", num, rank);
		fflush(stdout);
	}
	else {
		int src = (rank - 1);
		MPI_Recv(&num, 1, MPI_INT, src, rank, MPI_COMM_WORLD, &status);
		fprintf(stdout, "Number: %d received in process %d\n", num, rank);
		fflush(stdout);

		num++;
		int dest = (rank + 1) % size;
		MPI_Send(&num, 1, MPI_INT, dest, dest, MPI_COMM_WORLD);
		fprintf(stdout, "Number: %d sent from process %d to  process %d\n", num, rank, dest);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}