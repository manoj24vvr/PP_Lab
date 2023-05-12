#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]) {
	int rank, size, N, i, num;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	
	if (rank == 0) {
		N = size;
		int* arr = (int*)malloc(N * sizeof(int));
		printf("Enter array size-%d: ", N);
		fflush(stdout);
		for (i = 0;i < N;i++)
			scanf_s("%d", &arr[i]);
		for (i = 1;i < size;i++) {
			MPI_Send(&arr[i], 1, MPI_INT, i, i, MPI_COMM_WORLD);
			fprintf(stdout, "Number: %d sent from process %d to  process %d\n", arr[i], rank, i);
			fflush(stdout);
		}
		num = arr[rank];
		free(arr);
	}
	else {
		MPI_Recv(&num, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		fprintf(stdout, "Number: %d received in process %d\n", num, rank);
		fflush(stdout);
	}
	
	int prime = 1;

	for (i = 2;i <= num / 2;i++) {
		if (num % i == 0) {
			prime = 0;
			break;
		}
	}
	if (prime)
		fprintf(stdout, "%d is Prime\n",num);
	else
		fprintf(stdout, "%d is not Prime\n",num);

	MPI_Finalize();
	return 0;
}