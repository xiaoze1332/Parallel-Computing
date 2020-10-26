#include "mpi.h"
#include <stdio.h>

int main(int argc, char ** argv)
{
    int sba[1] = {-1}, sbb[1] = {1};
    int rba[1], rbb[1];
    int rank, nproc;

    int flag1, flag2;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Request request_1, request_2;
    MPI_Status status1, status2;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &nproc);


    if (rank == 0)
    {
        fprintf(stderr, "proc %d: sba = [%d]\n", rank, sba[0]);
        fprintf(stderr, "proc %d: sbb = [%d]\n", rank, sbb[0]);
        fflush(stderr);

        MPI_Isend(sba, 1, MPI_INT, 1, 0, comm, &request_1);
        MPI_Isend(sbb, 1, MPI_INT, 1, 0, comm, &request_2);

        MPI_Wait(&request_1, &status1);
        MPI_Wait(&request_2, &status2);
    }
    else if (rank == 1)
    {
        MPI_Irecv(rba, 1, MPI_INT, 0, MPI_ANY_TAG, comm, &request_1);
        MPI_Irecv(rbb, 1, MPI_INT, 0, 0, comm, &request_2);

        MPI_Test(&request_1, &flag1, &status1);
        MPI_Test(&request_2, &flag2, &status2);

        fprintf(stderr, "proc %d: rba = [%d], t = %f, flag1 = %d\n", rank, rba[0], MPI_Wtime(), flag1);
        fprintf(stderr, "proc %d: rbb = [%d], t = %f, flag2 = %d\n", rank, rbb[0], MPI_Wtime(), flag2);

        MPI_Wait(&request_1, &status1);
        MPI_Wait(&request_2, &status2);

        MPI_Test(&request_1, &flag1, &status1);
        MPI_Test(&request_2, &flag2, &status2);

        fprintf(stderr, "proc %d: rba = [%d], t = %f, flag1 = %d\n", rank, rba[0], MPI_Wtime(), flag1);
        fprintf(stderr, "proc %d: rbb = [%d], t = %f, flag2 = %d\n", rank, rbb[0], MPI_Wtime(), flag2);

        fflush(stderr);
    }

    MPI_Finalize();

    return 0;
}