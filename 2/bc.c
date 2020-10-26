#include "mpi.h"
#include <stdio.h>

#define BUF_SIZE 10

int main(int argc, char ** argv)
{
    int myid, nprocs, other;

    // Data sent and received.
    int sb[BUF_SIZE], rb[BUF_SIZE];

    MPI_Status status;

    // Initialize MPI env.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);    // Get process id.
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);  // Get total process number.

    // Fill the data array for different process.
    for (int i = 0; i < BUF_SIZE; ++i)
    {
        sb[i] = myid + i;
    }

    // Set another process number.
    if (myid == 0)
    {
        other = 1;
    }

    else if (myid == 1)
    {
        other = 0;
    }

    // Send and receive data in proc 0.
    if (myid == 0)
    {
        fprintf(stderr, "process %d of %d sending data...\n", myid, nprocs);
        MPI_Send(sb, BUF_SIZE, MPI_INT, other, 1, MPI_COMM_WORLD);

        fprintf(stderr, "process %d of %d receiving data...\n", myid, nprocs);
        MPI_Recv(rb, BUF_SIZE, MPI_INT, other, 1, MPI_COMM_WORLD, &status);
    }

    // Send and receive data in proc 1.
    if (myid == 1)
    {
        fprintf(stderr, "process %d of %d sending data...\n", myid, nprocs);
        MPI_Send(sb, BUF_SIZE, MPI_INT, other, 1, MPI_COMM_WORLD);
        
        fprintf(stderr, "process %d of %d receiving data...\n", myid, nprocs);
        MPI_Recv(rb, BUF_SIZE, MPI_INT, other, 1, MPI_COMM_WORLD, &status);
    }

    // Print something.
    fprintf(stderr, "Hello world, process %d of %d \n", myid, nprocs);

    // Finalize MPI env.
    MPI_Finalize();

    return 0;
}