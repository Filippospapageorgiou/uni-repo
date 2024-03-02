#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

struct results{
	char string[80];
	int  x;
};



int calc(int array[],int n);

int main(void)
{
	struct results result1,result2;
	FILE *fp,*fp2;
	fp=fopen("numbrs.txt","r");
	if(fp==NULL)
	{
		printf("Error opening file");
		exit(0);
	}
	int pin[20],i,temp1,temp2,temp3,x;
	srand(time(NULL));
	for(i=0; i<20; i++)
	{
		temp1=100+rand()%(1000-100+1);
		temp2=rand()%901-1000;
		temp3=rand()%2;
		if(temp3==0)
		 pin[i]=temp1;
		else
		 pin[i]=temp2; 
	}
	x=calc(pin,20);
	result1.x=x;
	strcpy(result1.string,"Rndom");
	printf("%d",result1.x);
	
	for(i=0; i<20; i++)
	{
		fscanf(fp,"%d",&pin[i]);
	}
	
	x=calc(pin,20);
	result2.x=x;
	strcpy(result2.string,"File");
	fp2=fopen("Results.dat","w");
	if(fp2==NULL)
	{
		printf("Error opening file");
		exit(0);
	}
	fprintf(fp2,"Main programm reslts1=%s results1=%d\n",result1.string,result1.x);
	fprintf(fp2,"Programm File reslts2=%s results2=%d",result2.string,result2.x);
	fclose(fp2);
	fclose(fp);
	return 0;
	
}

int calc(int array[],int n)
{
	int sum=0,sum2=0,x;
	int i;
	for(i=0; i<n; i++)
	{
		sum+=pow(array[i],2);
		sum2+=fabs(array[i]);
	}
	sum2=sum2*n;
	x=sum-sum2;
	return x;
}
