#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv)
{
	int my_rank;
	int p,k,res,finres,a1,b1,num;
	int source;
	int target;
	int tag1 = 50;
	int tag2 = 60;
	int endnum;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if (my_rank == 0)
	{
		printf("Dose plithos aritmon:\n");
		scanf("%d", &endnum);
		for (target = 1; target < p; target++)
		MPI_Send(&endnum, 1, MPI_INT, target, tag1, MPI_COMM_WORLD);
	}
	else
		MPI_Recv(&endnum, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD, &status);

	res = 0;
	num = endnum/p;
	a1 = (my_rank * num) + 1;
	b1 = a1 + num - 1;
	for (k=a1; k<=b1; k++)
		res = res + (k*k);

	if (my_rank != 0)
	{
		MPI_Send(&res, 1, MPI_INT, 0, tag2, MPI_COMM_WORLD);
	}
	else
	{
		finres = res;
		printf("\n Apotelesma of process %d: %d\n", my_rank, res);
		for (source = 1; source < p; source++)
		{
			MPI_Recv(&res, 1, MPI_INT, source, tag2,
							MPI_COMM_WORLD, &status);
			finres = finres + res;
			printf("\n Apotelesma of process %d: %d\n", source, res);
		}
	printf("\n\n\n Teliko Apotelesma: %d\n", finres);
	}
	MPI_Finalize();
}
