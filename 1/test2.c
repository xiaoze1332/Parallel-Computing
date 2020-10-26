#include <stdio.h>
#include <omp.h>
#include <mpi.h>

int main(int argc, char const *argv[])
{
	int myid,totalid;
	#pragma	omp	parallel	private(myid,totalid)
	{
		myid = omp_get_thread_num();
		totalid	=	omp_get_thread_num();
		printf("hello world from %d/%d.\n",myid,totalid);
	}
	return 0;
}