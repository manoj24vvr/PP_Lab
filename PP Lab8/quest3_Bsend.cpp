#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>
#define BUF_SIZE 2^16

int main(int argc, char* argv[]) {
	int rank, size, N, i, num;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	N = size;
	int* arr = (int*)malloc(N * sizeof(int));
	int buf[BUF_SIZE];
	MPI_Buffer_attach(buf, BUF_SIZE * sizeof(int));

	if (rank == 0) {
		printf("Enter array size-%d: ", N);
		fflush(stdout);
		for (i = 0;i < N;i++)
			scanf_s("%d", &arr[i]);
		for (i = 1;i < size;i++) {
			MPI_Bsend(&arr[i], 1, MPI_INT, i, i, MPI_COMM_WORLD);
			fprintf(stdout, "Number: %d sent from process %d to  process %d\n", arr[i], rank, i);
			fflush(stdout);
		}
	}
	else if (rank % 2 == 0) {
		
		MPI_Recv(&num, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		//Detach_buffer(&buf);
		int sq = num * num;
		fprintf(stdout, "Number: %d received in process %d\nSquare: %d\n", num, rank, sq);
		fflush(stdout);
	}
	else {
		MPI_Recv(&num, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		int cube = num * num * num;
		fprintf(stdout, "Number: %d received in process %d\nCube: %d\n", num, rank, cube);
		fflush(stdout);
	}
	free(arr);
	MPI_Finalize();
	return 0;
}