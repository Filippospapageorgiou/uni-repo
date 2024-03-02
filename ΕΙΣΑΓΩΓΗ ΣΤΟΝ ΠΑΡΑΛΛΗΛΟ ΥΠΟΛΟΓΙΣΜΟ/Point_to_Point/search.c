#include <stdio.h>
#include "mpi.h"
int main(int argc, char** argv)
{
  int my_rank, size;
  int source, dest;
  int tag1= 50;
  int tag2 = 60; 
  int tag3 =70;
  int found = 0;
  int other_found;
  int k, code, namelen;
  int data[10];
  MPI_Status status;
  char proc_name[MPI_MAX_PROCESSOR_NAME];
  char other_proc_name[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(proc_name, &namelen);


  for(k=0; k<10; k++)
   data[k]=my_rank+k;
  if(my_rank==0)
  {
  	printf("Dose enan kodiko anazitis:");
  	scanf("%d",&code);
  	for(dest=1; dest<size; dest++){
  		MPI_Send(&code,1,MPI_INT,dest,tag1,MPI_COMM_WORLD);
  	}
  }else{
  	MPI_Recv(&code,1,MPI_INT,0,tag1,MPI_COMM_WORLD,&status);
  } 
  for(k=0; k<10; k++){
  	if(data[k]==code)
  	 found=1;
  }

  if(my_rank!=0){
     MPI_Send(&found, 1, MPI_INT, 0, tag2, MPI_COMM_WORLD);
  	 MPI_Send(proc_name, namelen+1, MPI_CHAR, 0, tag3, MPI_COMM_WORLD); 
  }
  if(my_rank==0){
  	for(source=1; source<size; source++){
  		MPI_Recv(&other_found, 1, MPI_INT, source, tag2, MPI_COMM_WORLD, &status);  
  		MPI_Recv(other_proc_name, 50, MPI_CHAR, source, tag3, MPI_COMM_WORLD,
  		&status); 
  		if(other_found)
  		 printf("\nCode %d Found in database of process %d on %s\n",code,source,other_proc_name);
  		 
  	}
  	if(found)
  	 	printf("\n Code %d found in process %d on %s \n", code, my_rank, proc_name); 
  }

     MPI_Finalize();
}
