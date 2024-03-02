
#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

#define SIZE 100

int main(int argc,char **argv){
	int my_rank,p,k,b,size;
	int root,matrixA[SIZE],loc_num,loc_matrix[SIZE],loc_res[SIZE],namelen,final_res[SIZE];

	char proc_name[MPI_MAX_PROCESSOR_NAME];


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Get_processor_name(proc_name, &namelen);


	if(my_rank==0){
		printf("YPOLOGISMOS THS PARASTASHS b *A \n\n");
		printf("Dwse tin timi tou B:\n");
		scanf("%d",&b);
		printf("Dwse to mikos tou pinaka A:\n");
		scanf("%d",&size);
		printf("DOSE TA STOIXEIA TOU PINAKA A MIKOYS %d:\n",size);
		for(k=0; k<size; k++)
		 scanf("%d",&matrixA[k]);
	}
	root=0;

	MPI_Bcast(&size,1,MPI_INT,root,MPI_COMM_WORLD);
	MPI_Bcast(&b,1,MPI_INT,root,MPI_COMM_WORLD);
	loc_num=size/p;

	MPI_Scatter(matrixA,loc_num,MPI_INT,loc_matrix,loc_num,MPI_INT,root,MPI_COMM_WORLD);
    printf("\n-----------------------------------------------------\n");
	for(k=0; k<loc_num; k++){
	  loc_res[k]=b*loc_matrix[k];
      printf("\nstep : %d %d, ",k,loc_res[k]);
    }
    printf("\n-----------------------------------------------------\n");


	printf("\n Procces %d on %s : local results are : ",my_rank,proc_name);
	  for (k=0; k<loc_num; k++) printf("%d ", loc_res[k]);
	  printf("\n\n");

	  root=0;
	  MPI_Gather(loc_res,loc_num,MPI_INT,final_res,loc_num,MPI_INT,root,MPI_COMM_WORLD);

	  if(my_rank==0){
	  	printf("Teliko apotelesma %d * A =\n",b);
	  	for(k=0; k<size; k++)
	  	  printf("%d, ",final_res[k]);

	  	 printf("\n\n");
	  }
	  MPI_Finalize();
}
