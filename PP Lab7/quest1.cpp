#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define X 5

int power(int num) {
	int i, pow = 1;
	for (int i = 1;i <= num;i++)
		pow *= X;
	return pow;
}

int main(int argc, char* argv[]) {
	int myid, numprocs, namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Get_processor_name(processor_name, &namelen);


	if (myid == 0)
		printf("Value of Integer X is: %d\n...", X);
	printf("\n%s: %d ^ %d = %d\n", processor_name, X, myid, power(myid));
	MPI_Finalize();

	return 0;
}