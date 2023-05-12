#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char** argv) {
    int rank, size;
    int number, cube;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        printf("Enter 5 numbers:\n");
        for (int i = 0; i < 5; i++) {
            scanf_s("% d", &number);
            MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);
        }
    } else {
        for (int i = 0; i < 5; i++) {
            scanf_s("% d", &number);
            MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);
            cube = pow(number, 3);
            MPI_Send(&cube, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    if (rank == 0) {
        printf("The cubes of the given values are:\n");
        for (int i = 0; i < 5; i++) {
            for (int j = 1; j < size; j++) {
                MPI_Recv(&cube, 1, MPI_INT, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("%d ", cube);
            }
            scanf_s("%d", &number);
            MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}