#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define num1 7
#define num2 5

int main(int argc, char* argv[]) {
	int myid, numprocs, namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Get_processor_name(processor_name, &namelen);

	if (myid == 0) {
		printf("Addition\t");
		printf("%d + %d = %d\n", num1, num2, num1 + num2);
	}
	else if(myid == 1) {
		printf("Subtraction\t");
		printf("%d - %d = %d\n", num1, num2, num1 - num2);
	}
	else if (myid == 2) {
		printf("Multiplication\t");
		printf("%d * %d = %d\n", num1, num2, num1 * num2);
	}
	else if (myid == 3) {
		printf("Division\t");
		if (num2 == 0)
			printf("Cannot perform division\n");
		else {
			float res;
			res = num1 / num2;
			printf("%d / %d = %.2f\n", num1, num2, res);
		}
		
	}
	MPI_Finalize();

	return 0;
}