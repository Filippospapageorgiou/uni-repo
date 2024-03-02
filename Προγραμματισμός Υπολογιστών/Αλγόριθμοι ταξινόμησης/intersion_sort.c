#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define TRUE 1
#define FALSE 0



void init_array(int *pinakas,int n, int a, int b);
void print_array(int *pinakas,int n);
void swap(int *a, int *b);
void insertion_sort(int *pinakas, int n);

main()
{
	
	int pinakas[SIZE];
	int i,j,n=15;
	
	init_array(pinakas,n,1,100);
	
	printf("\t\tEpidiksi Insertion sort\n\n");
	printf("Arxi : ");
	print_array(pinakas,n);
	printf("\n\n");
	
	printf("Meta : ");
	insertion_sort(pinakas,n);
	print_array(pinakas,n);
}
	
	
	
	
void  init_array(int *pinakas,int n, int a,  int b)
	{
		
		int i;
		
		srand(time(NULL));
		
		for(i=0; i<n; i++)
		 pinakas[i]=a+rand()%(b-a+1);
		
	}
	
void print_array(int *pinakas, int n)
{
	
	int i;
	
	printf("[");
	for(i=0; i<n-1; i++)
	 printf("%2d,",pinakas[i]);
	printf("%d]",pinakas[n-1]);
	}
	
void swap(int *a, int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
	}	

void insertion_sort(int *pinakas, int n)
{
	int i,j;
	
	for(i=0; i<n; i++)
	{
		for(j=i; j>=1; j--)
		{
			if (pinakas[j]<pinakas[j-1])
			  swap(&pinakas[j], &pinakas[j-1]);
			 else
			  break; 
		}
	}
	
	}	
