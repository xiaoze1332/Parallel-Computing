#include	<stdio.h>
#include	<mpi.h>

int main(int argc, char const *argv[])
{
	int	myid,totalid;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Comm_size(MPI_COMM_WORLD,&totalid);
	printf("Hello World from %d/%d.\n",myid,totalid);
	MPI_Finalize();
	return 0;
}