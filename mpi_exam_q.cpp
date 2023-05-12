#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]) {
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int N=size, M;
	int *arr=NULL;

	if (rank == 0) {
		printf("Enter value of M: ");
		fflush(stdout);
		scanf_s("%d", &M);
		//for (int i = 0; i < N; i++)
		arr = (int*)malloc(M * N * sizeof(int));
		printf("Enter values of Matrix: ");
		fflush(stdout);
		for (int i = 0; i < N; i++) {
			printf("Row %d:\t", i + 1);
			fflush(stdout);
			for (int j = 0; j < M; j++) {
				scanf_s("%d", &arr[i * M + j]);
			}
		}
		printf("Matrix: ");
		fflush(stdout);
		for (int i = 0; i < N; i++) {
			printf("Row %d:\t", i + 1);
			fflush(stdout);
			for (int j = 0; j < M; j++) {
				printf("%d\t", arr[i * M + j]);
			}
			printf("\n");
		}
		fflush(stdout);
	}
	MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
	int* local_arr = (int*)malloc(M * sizeof(int));
	MPI_Scatter(arr, M, MPI_INT, local_arr, M, MPI_INT, 0, MPI_COMM_WORLD);
	/*printf("Array: ");
	fflush(stdout);
	for (int i = 0; i < M; i++) {
		printf("%d\t", local_arr[i]);
		fflush(stdout);
	}*/
	for (int i = 0; i < M; i++) {
		if (local_arr[i] % 2 == 0)
			local_arr[i] = 0;
		else
			local_arr[i] = 1;
	}
	MPI_Gather(local_arr, M, MPI_INT, arr, M, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		printf("Transformed matrix: \n");
		fflush(stdout);
		for (int i = 0; i < N; i++) {
			printf("Row: %d\t", i + 1);
			fflush(stdout);
			for (int j = 0; j < M; j++) {
				printf("%d\t", arr[i * M + j]);
			}
			printf("\n");
		}
		fflush(stdout);
	}
	free(local_arr);
	free(arr);
	MPI_Finalize();
	return 0;
}