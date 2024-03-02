#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void calc(int m,int n,int k,int **pin);
void print_calc(int m,int n,int **pin);
int play(int m,int n,int **pin,int **blank,int x,int y);
void free_array(int **blank,int **pin,int m);
void get_space(int *m,int *n);
void fill_array(int **blank,int **pin,int m,int n);
void pick(int *x,int *y,int m,int n);
int get_k();

int main(int argc, char **argv) 
{
	
	int i,k,m,n,**pin,**blank,cnt=0,flag;
	int x,y,choice;
		
	system ("chcp 1253");
	printf("---�������� ������������---\n\n");
	srand(time(NULL));
	
	get_space(&m,&n);

	pin=malloc(sizeof(int*)*m);
	if(!pin)
	{
		printf("\n\n�������� ��������� ������\n");
		exit(0);
	}
	for(i=0; i<m; i++)
	{
		pin[i]=malloc(sizeof(int)*n);
		if(!pin[i])
		{
			printf("\n\n�������� ��������� ������");
			exit(0);
		}
	}
	
	blank=malloc(sizeof(int*)*m);
	if(!blank)
	{
		printf("\n\n�������� ��������� ������\n");
		exit(0);
	}
	for(i=0; i<m; i++)
	{
		blank[i]=malloc(sizeof(int)*n);
		if(!blank[i])
		{
			printf("\n\n�������� ��������� ������");
			exit(0);
		}
	}
	
	
	
	k=get_k();
	flag=(m*n)-k; 
	fill_array(blank,pin,m,n);
	calc(m,n,k,pin);
	//print_calc(m,n,pin);
	while(1)
	{
	 cnt++;
	 pick(&x,&y,m,n);
	 if(play(m,n,pin,blank,x,y)==1)
	 {
	 	printf("\n������ ������� �����...\n");
	 	print_calc(m,n,pin);
	 	printf("\n��� �� ������� ���� (YES->1) � (No->0):");
	 	scanf("%d",&choice);
	 	if(choice==1)
	 	{
	 		cnt=0;
	 		fill_array(blank,pin,m,n);
	 		calc(m,n,k,pin);
		}
		else
		{
			printf("\n������ ����������!\n");
			printf("Press ane key to continue...");
			break;
		}
	 }
	if(cnt==flag)
	{
	   	printf("\n--!!!!��������!!!---\n");
	 	printf("\n��� �� ������� ���� (YES->1) � (No->0):");
	 	scanf("%d",&choice);
	 	if(choice==1)
	 	{
	 		cnt=0;
	 		fill_array(blank,pin,m,n);
	 		calc(m,n,k,pin);
		}
		else
		{
			printf("\n������ ����������!\n");
			printf("Press ane key to continue...");
			break;
		}
	 	
	}	
}
	free_array(blank,pin,m);
	
	return 0;
}
int play(int m,int n,int **pin,int **blank,int x,int y)
{
	int i,j;
	blank[x][y]=pin[x][y];
	if(blank[x][y]==9)
	 return 1;
	printf("\n������������\n");
	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
		{
			if(blank[i][j]==10)
			 printf("|_|");
			else if(blank[i][j]>=0 && blank[i][j]<=8)
			 printf("|%d|",blank[i][j]);  
		}
		printf("\n");
	}
	return 0;
	
}

void pick(int *x,int *y,int m,int n)
{
	printf("\n���� ������������� ��� �������:\n");
	printf("���� �� � ��� (0-%d):",m-1);
	scanf("%d",x);
	printf("���� �� y ��� (0-%d):",n-1);
	scanf("%d",y);
}



void fill_array(int **blank,int **pin,int m,int n)
{
	int i,j;
	
	for (i=0; i<m; i++)	
		for (j=0; j<n; j++)		
		 pin[i][j]=0;
	
	for(i=0; i<m; i++)
	 for(j=0; j<n; j++)
	   blank[i][j]=10;	 
}



void calc(int m,int n,int k,int **pin)
{
	int i,j;
	int cnt;
    for (i=0; i<m; i++)
	{		
		for (j=0; j<n; j++)
		{	
			if(pin[i][j]!=9 && k>0)
			{
			pin[rand() %m][rand() %n]=9;
			k=k-1;
			}
		}
	}
	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
		{
			cnt=0;
			if(j==0 && i==0)
			{
				if((pin[i][j+1]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i+1][j]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i+1][j+1]==9) && (pin[i][j]!=9))
				 cnt++;
				if(pin[i][j]!=9)
				 pin[i][j]=cnt;   
			}
			if(j==0 && (i>0 && i<m-1))
			{
				if((pin[i][j+1]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i+1][j]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i+1][j+1]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i-1][j]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i-1][j+1]==9) && (pin[i][j]!=9))
				 cnt++;    
				if(pin[i][j]!=9)
				 pin[i][j]=cnt;  
			}
			if(i==0 && j!=0)
			{
				if((pin[i][j+1]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i+1][j]==9) && (pin[i][j]!=9))
				 cnt++;         
				if((pin[i+1][j+1]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i][j-1]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i+1][j-1]==9) && (pin[i][j]!=9))
				 cnt++;
				if(pin[i][j]!=9)
				 pin[i][j]=cnt;             
			}
			if(i==m-1)
			{
				if(j==0)
				{
			 	 if((pin[i-1][j]==9) && (pin[i][j]!=9))
				  cnt++;
				 if((pin[i-1][j-1]==9) && (pin[i][j]!=9))
				 cnt++;
				 if((pin[i][j+1]==9) && (pin[i][j]!=9))
				 cnt++; 
				if(pin[i][j]!=9)
				 pin[i][j]=cnt;   	
				}
				if(j!=0)
				{
				 if((pin[i-1][j]==9) && (pin[i][j]!=9))
				  cnt++;
				 if((pin[i-1][j-1]==9) && (pin[i][j]!=9))
				 cnt++;
				 if((pin[i][j+1]==9) && (pin[i][j]!=9))
				 cnt++;
				 if((pin[i][j-1]==9) && (pin[i][j]!=9))
				 cnt++;     
				if(pin[i][j]!=9)
				 pin[i][j]=cnt; 	
				}
			}
			if(j==n-1 && (i>0 && i<m-1))
			{
				if((pin[i-1][j]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i-1][j-1]==9) && (pin[i][j]!=9))
				 cnt++;       
				if((pin[i][j-1]==9) && (pin[i][j]!=9))
				 cnt++;   
				if((pin[i+1][j]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i+1][j-1]==9) && (pin[i][j]!=9))
				 cnt++; 
				if(pin[i][j]!=9)
				 pin[i][j]=cnt;     
			}
			if((i!=m-1 && i!=0) && (j!=0 && j!=n-1))
			{
				if((pin[i-1][j]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i-1][j-1]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i][j-1]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i+1][j]==9) && (pin[i][j]!=9))
				 cnt++;   
				if((pin[i+1][j-1]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i+1][j+1]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i][j+1]==9) && (pin[i][j]!=9))
				 cnt++;
				if((pin[i-1][j+1]==9) && (pin[i][j]!=9))
				 cnt++;
				if(pin[i][j]!=9)
				 pin[i][j]=cnt;    
			}
		}
	}
	
}

void get_space(int *m,int *n)
{
    printf("�������� �������� ��� ��������� ���� � x � ������\n");
	printf("�������� �������� �� m:");
	scanf("%d",m);
	printf("�������� �������� �� n:");
	scanf("%d",n);
}


int get_k()
{
	int temp;
	printf("�������� �������� �� ������ ��� ������ k\n");
	printf("�������� �������� �� k:");
	scanf("%d",&temp);
	return temp;
}

void print_calc(int m,int n,int **pin)
{
	printf("\n������� �� ������\n");
	int i,j;
    for (i=0; i<m; i++)
	{		
		for (j=0; j<n; j++)
		{
		if (pin[i][j]!=9)
		 printf("|%d|",pin[i][j]);
		else
		 printf("|*|");
		}
		printf("\n");	
	}
}

void free_array(int **blank,int **pin,int m)
{
	int i;
	for(i=0; i<m; i++)
	  free(pin[i]);
	free(pin);	
	
	for(i=0; i<m; i++)
	 free(blank[i]);
	free(blank); 
}

