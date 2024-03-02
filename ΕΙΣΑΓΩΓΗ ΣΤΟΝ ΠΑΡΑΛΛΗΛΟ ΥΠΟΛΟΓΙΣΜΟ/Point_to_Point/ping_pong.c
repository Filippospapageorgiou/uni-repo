#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	int numtasks,rank,dest,src,tag=1,i=0,limit=0;
	char msg1[15],msg2[15];
	MPI_Status stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	sprintf(msg1,"Test");
	


    
    while(i<limit){

	if(rank==0){
		dest=1;
		src=1;
			MPI_Send(msg1,15,MPI_CHAR,dest,tag,MPI_COMM_WORLD);
			sprintf(msg1, "\0");
			MPI_Recv(msg1, 15, MPI_CHAR, src, tag,
			 MPI_COMM_WORLD, &stat); 
			printf("Process %d Message = %s \n", rank, msg1);
			i++;
			sleep(2);
	}
	else if(rank==1){
		dest=0;
		src=0;
			 sprintf(msg2, "\0");
			 MPI_Recv(msg2, 15, MPI_CHAR,src, tag,
			 MPI_COMM_WORLD, &stat);
			 printf("Process %d Message = %s \n", rank, msg2);
			 sleep(2);
			 i++;
			 MPI_Send(msg2, 15, MPI_CHAR, dest, tag,
			 MPI_COMM_WORLD);
		
	}

	}
	MPI_Finalize();
}
