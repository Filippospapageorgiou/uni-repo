/* Ypologismo S = 1^2 + 2^2 + .... (n-1)^2*/

#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
    int my_rank,size,k,a1_local,a2_local;
    int local_num,endnum,local_res,final_res,namelen;
    int root=0;

    char proc_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Get_processor_name(proc_name,&namelen);

    if(my_rank==root){
     printf("Dwse plithos arithmon : \n");
     scanf("%d",&endnum);   
    }
    MPI_Bcast(&endnum,1,MPI_INT,root,MPI_COMM_WORLD);

    local_res=0;
    local_num=endnum/size;

    a1_local=(my_rank*local_num) + 1;
    a2_local=local_num + a1_local - 1;

    for(k=a1_local; k<a2_local; k++){
        local_res=local_res + (k*k);
    }
    printf("\n Process %d on %s : local result = %d \n", my_rank,
proc_name, local_res);
    MPI_Reduce(&local_res,&final_res,1,MPI_INT,MPI_SUM,root,MPI_COMM_WORLD);

    if (my_rank==root)
    {
        printf("\n Total result for N = %d is equal to : %d \n", endnum,
final_res); 
    }
    MPI_Finalize();

}