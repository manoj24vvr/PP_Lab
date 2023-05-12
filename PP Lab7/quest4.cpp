#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

char toggle(char ch) {
	if (ch >= 'A' && ch <= 'Z')
		return ch + 32;
	else if (ch >= 'a' && ch <= 'z')
		return ch - 32;
}

int main(int argc, char* argv[]) {
	int myid, numprocs, namelen, len;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	char str[] = "HeLLo";
	len = strlen(str);
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Get_processor_name(processor_name, &namelen);

	if (myid==0 && numprocs != len) {
		printf("Number of processors isn't sufficient\t");
	}
	else{
		char ch;
		ch = str[myid];
		str[myid] = toggle(str[myid]);
		printf("Id %d - %c to %c\n", myid, ch, str[myid]);
	}

	MPI_Finalize();

	return 0;
}