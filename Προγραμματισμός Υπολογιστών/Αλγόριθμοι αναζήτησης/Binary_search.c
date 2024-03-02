#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define TRUE 1
#define FALSE 0

void init_sorted_array(int *pinakas, int n, int a, int max_step);
void print_array(int *pinakas, int n);
void print_partial_array(int *pinakas, int start, int finish, int n);
int binary_search(int *pinakas, int n, int i); 

main()
{
	int pinakas[SIZE];
	int i,found,N=20;
	
	init_sorted_array(pinakas,N,1,2);
	i=1+rand()%30;
	
	printf("Pinakas dedomewn: \n");
	print_array(pinakas,N);
	printf("\n\nTo stoixeio einai i=%d",i);
	printf("\n\n");
	
	printf("----------------------\n\n");
	
	found=binary_search(pinakas,N,i);
	
     if(found)
     printf("To stoixeio vrethike!");
     else
     printf("-1");
	   
printf("\n\n");	   
}

void init_sorted_array(int *pinakas, int n, int a, int max_step)
{
	int i;
	
	srand(time(NULL));
	
	pinakas[0]=a;
	for(i=1; i<n; i++)
	    pinakas[i]=pinakas[i-1]+rand()%max_step+1;
}

void print_array(int *pinakas, int n)
{
	int i;
	
	printf("[");
	for(i=1 ; i<n; i++)
	{
		printf("%2d,",pinakas[i]);
	}
	printf("%2d]",pinakas[n-1]);
}

void print_partial_array(int *pinakas, int start, int finish, int n)
{
	int i;
	printf("[");
	for(i=0; i<n; i++)
	{
		printf(" ",pinakas[i]);
	}
	for(i=start; i<=finish; i++)
	{
		printf("%3d",pinakas[i]);
	}
	for(i=finish; i<n-1; i++)
	{
		printf(" ",pinakas[i]);
	}
	printf("]");
}

int binary_search(int *pinakas, int n, int i)
{
	
	int start,finish,middle;
	
	start=0;
	finish=n-1;
	while(start<=finish)
	{
		middle=(start+finish)/2;
	
		if(i==pinakas[middle])
		{
			return 1;
		}
		else if(i<pinakas[middle])
		    finish=middle-1;
		else
		     start=middle+1;
		
	}
	return 0;
	
	
}
