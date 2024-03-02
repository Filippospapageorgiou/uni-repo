#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	int i, my_rank, x, y;
	MPI_Status status;
	MPI_Request request;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	if (my_rank == 0) { /* P0 */
		x=10;
		MPI_Isend(&x,1,MPI_INT,1,0,MPI_COMM_WORLD,&request);
		MPI_Recv(&y,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);
		MPI_Wait(&request,&status);
		printf("I am thread 0 with x=%d and y=%d\n", x, y);
	} else if (my_rank == 1) { /* P1 */
		y=20;
		MPI_Isend(&y,1,MPI_INT,0,0,MPI_COMM_WORLD,&request);
		MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		MPI_Wait(&request,&status);
		printf("I am thread 1 with x=%d and y=%d\n", x, y);
	}
	MPI_Finalize();
}
