#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define TRUE 1
#define FALSE 0


void init_sorted_array(int *pinakas, int n, int a, int max_step);
void print_array(int *pinakas, int n);
void print_partial_array(int *pinakas, int start, int finish, int n);
int binary_search(int *pinakas, int n, int x); 
int linear_search(int *pinakas, int n, int x);
main()
{
	int pinakas[SIZE];
	int x,pl1,pl2,N=20;

	init_sorted_array(pinakas,N,1,2);
	x=1+rand()%30;
	
	printf("\nPinakas dedomewn: \n");
	print_array(pinakas,N);
	printf("\n\nTo stoixeio einai x=%d",x);
	printf("\n\n");
	
	printf("----------------------\n\n");
	
	pl1=binary_search(pinakas,N,x);
	pl2=linear_search(pinakas,N,x);
	printf("\n\n%d,%d",pl1,pl2);
	if(pl1>pl2)
	{
	 printf("\n\nNikitis einai i seiriaki  anazitisi!");
    }
	else if(pl2>pl1)
	{
	 printf("\n\nNikitis einai i diadiki anazitisi!");
    }
	else
	printf("\n\nTo stoixeio den vrethike!");



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

int binary_search(int *pinakas, int n, int x)
{
	
	int start,finish,middle,pl;
	
	pl=0;
	start=0;
	finish=n-1;
	while(start<=finish)
	{
		pl+=1;
		middle=(start+finish)/2;
	
		if(x==pinakas[middle])
		{
			return pl;
		}
		else if(x<pinakas[middle])
		    finish=middle-1;
		else
		     start=middle+1;
		
	}
	return 0;
	
	
}

int linear_search(int *pinakas, int n, int x)
{
	
	int i,pl;
	pl=0;
	for(i=0; i<n; i++)
	{
		pl+=1;
		if(x==pinakas[i])
		return pl;
	}
	return 0;
	
}


