#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define TRUE 1
#define FALSE 0



void init_array(int *pinakas,int n, int a, int b);
void print_array(int *pinakas,int n);
int linear_search(int *pinakas, int n, int x);

main()
{
	
	int pinakas[SIZE];
	int i,x,found,N=20;
	
	init_array(pinakas,N,1,20);
	x=1+rand()%20;
	
	printf("Pinakas dedomenon: \n");
	print_array(pinakas,N);
	printf("\nStoixeio x=%d",x);
	printf("\n\n");
	
	
	found=linear_search(pinakas,N,x);

	if(found)
	   printf("To stoixeio vrethike");
	else 
	    printf("To stoixeio den brethike");

	}
	
	
	
	
void  init_array(int *pinakas,int n, int a,  int b)
	{
		
		int i;
		
		srand(time(NULL));
		
		for(i=0; i<=n; i++)
		 pinakas[i]=a+rand()%(b-a+1);
		
	}
	
void print_array(int *pinakas, int n)
{
	
	int i;
	
	printf("[");
	for(i=0; i<=n; i++)
	printf("%d, ",pinakas[i]);
	
printf("]");
	}
	
int linear_search(int *pinakas, int n, int x)
{
	int i,found;
		found=FALSE;
	for(i=0; i<n; i++)
	{
		if(pinakas[i]==x)
		{
           return 1;
		}
	}
	return 0;


	
}
	
