#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]) {
	int rank, size,i,num;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	if (rank == 0) {
		printf("Enter a number: ");
		fflush(stdout);
		scanf_s("%d", &num);
		for (int i = 1;i < size;i++) {
			MPI_Send(&num, 1, MPI_INT, i, i, MPI_COMM_WORLD);
			fprintf(stdout, "Number: %d sent from process %d to  process %d\n", num, rank, i);
			fflush(stdout);
			num++;
		}
	}
	else {
		MPI_Recv(&num, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		fprintf(stdout, "Number: %d received in process %d\n", num, rank);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}