#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[]){
	 int rank;
	 double var;

	 MPI_Init(&argc,&argv);
	 MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	 
     if(rank==1) var=10.5;
     MPI_Bcast(&var,1,MPI_DOUBLE,1,MPI_COMM_WORLD);
     printf("Proccess %d var=%f\n",rank,var);


     MPI_Finalize();

}


     
