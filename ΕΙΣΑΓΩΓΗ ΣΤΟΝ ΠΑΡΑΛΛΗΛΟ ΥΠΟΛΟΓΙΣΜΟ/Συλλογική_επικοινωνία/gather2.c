#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define SIZE 100

int main(int argc,char *argv[]){
    int my_rank,p,k,n,size,root;
	int namelen,loc_res[SIZE],res[SIZE];
    int locala1,locala2,local_num;

	char proc_name[MPI_MAX_PROCESSOR_NAME];


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Get_processor_name(proc_name, &namelen);
    root=0;
    if(my_rank==root){
        printf("Dwse to (n):\n");
        scanf("%d",&n);
    }
    MPI_Bcast(&n,1,MPI_INT,root,MPI_COMM_WORLD);
    printf("\nProcces : %d var : %d ",my_rank,n);

    local_num=n/p;
    locala1=(my_rank * local_num) + 1;
    locala2=local_num + locala1 - 1;
    printf("\n-----------------------------\n");
    for(int i=locala1; i<locala2; i++){
        loc_res[i]=i*i;
        printf("%d, ",loc_res[i]);
    }
    printf("\n-----------------------------\n");

    MPI_Gather(loc_res,local_num,MPI_INT,res,local_num,MPI_INT,root,MPI_COMM_WORLD);
    if(my_rank==root){
        for(int i=0; i<n; i++)
         printf("%d, ",res[i]);
    }






    MPI_Finalize();
}