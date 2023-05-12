#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>
#define WORD_SIZE 20

int main(int argc, char *argv[]) {
	int rank, size,i;
	char str[WORD_SIZE],toggle[WORD_SIZE];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	if (rank == 0) {
		printf("Enter a word: ");
		fflush(stdout);
		scanf_s("%[^\n]%*c", &str, (unsigned)_countof(str));
		MPI_Ssend(&str, WORD_SIZE, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
		fprintf(stdout, "Word: %s sent from process %d\n", str, rank);
		fflush(stdout);
		MPI_Recv(&toggle, WORD_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
		fprintf(stdout, "Toggled word: %s received in process %d\n", toggle, rank);
		fflush(stdout);
	}
	else {
		MPI_Recv(&str, WORD_SIZE, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
		fprintf(stdout, "Word: %s received in process %d\n", str, rank);
		fflush(stdout);
		for (i = 0;str[i] != '\0';i++) {
			if (str[i] >= 'A' && str[i] <= 'Z')
				toggle[i] = str[i] + 32;
			else if (str[i] >= 'a' && str[i] <= 'z')
				toggle[i] = str[i] - 32;
		}
		toggle[i] = '\0';
		MPI_Ssend(&toggle, WORD_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		fprintf(stdout, "Toggled word: %s sent from process %d\n", toggle, rank);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}
