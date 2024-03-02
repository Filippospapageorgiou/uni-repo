#include <stdio.h>
#include <stdlib.h>

void Get_nums(int *pin,int N);
int Found(int *pin,int size,int flag);
void getlim1(int *x1,int *x2);
void getlim2(int *y1,int *y2);
void sort_array(int *pin,int n);
void ejades(int *pin,int n, int *matrix, int x1, int x2, int y1,int y2,int *count,int *cnt1,int *cnt2);
void makesix_array(int *six,int i, int j, int k,int l,int m,int n,int *pin);
void print(int *six);
int Check_ev(int *pin,int n,int x1,int x2);
int Check_sum(int *pin,int n,int y1,int y2);
void prinstats(int N,int count,int cnt1,int cnt2,int *matrix);
void get_matrix(int *matrix,int *six);

int main(void)
{
	int N,*pin,*matrix,x1,x2,y1,y2,count,cnt1,cnt2,i;
	
	
	system("chcp 1253");
	printf("----���������� �������----\n");
	
	printf("�������� � ������������� ��������� ��� �������� [1...49] �� (7<�<49):\n");
    do{
		printf("�������� �� N:");
		scanf("%d",&N);
	}while(N<7 || N>49);
	
	pin=(int*)malloc(sizeof(int)*N);
	if(!pin)
	{
		printf("����� ��� ������� ������");
		exit(0);
	}
	
	matrix=(int*)malloc(sizeof(int)*49);
	if(!matrix)
	{
		printf("����� ��� ������� ������");
		exit(0);
	}
	for(i=0; i<49; i++)
	 *(matrix+i)=0;
	
	
	Get_nums(pin,N);
	getlim1(&x1,&x2);
	getlim2(&y1,&y2);
    sort_array(pin,N);
    ejades(pin,N,matrix,x1,x2,y1,y2,&count,&cnt1,&cnt2);
	prinstats(N,count,cnt1,cnt2,matrix);
	free(pin);
	free(matrix);
}



void Get_nums(int *pin,int N)
{
	int i;
	for(i=0; i<N; i++)
	{
		do
		{
			printf("�������� ��� %d� ������: ",i+1);
			scanf("%d",&(*(pin+i)));
		}while(*(pin+i)<1 || *(pin+i)>49 || Found(pin,i,*(pin+i)));
	}
}

int Found(int *pin,int size,int flag)
{
	int i;
	for(i=0; i<size; i++)
	 if(*(pin+i)==flag)
	  return 1;
	return 0; 
}

void getlim1(int *x1,int *x2)
{
	printf("\n���� �� ������ �������� �1,�2 ������ ����: 0<=�1<=�2<=6\n");
	do{
		printf("���� �� �1:");
		scanf("%d",x1);
	}while(*x1<0 || *x1>6);
	do{
		printf("���� �� �2:");
		scanf("%d",x2);
	}while(*x2<*x1 || *x2>6);
}

void getlim2(int *y1,int *y2)
{
	printf("\n���� ������ �������� �1,�2 ������ ����: 21<=�1<=�2<=279\n");
	do{
		printf("���� �� Y1:");
		scanf("%d",y1);
	}while(*y1<21 || *y1>279);
	do{
		printf("���� �� Y2:");
		scanf("%d",y2);
	}while(*y2<*y1 || *y2>279);
}

void sort_array(int *pin,int n)
{
	int i,j,temp;
	for(i=0; i<n; i++)
	{
		for(j=n-1; j>=i+1; j--)
		{
			if(*(pin+j)<*(pin+(j-1)))
		    {
		    	temp=*(pin+j);
		    	*(pin+j)=*(pin+(j-1));
		    	*(pin+(j-1))=temp;
			}
			 
	     }
	}
	
}

void ejades(int *pin,int N, int *matrix, int x1, int x2, int y1,int y2,int *count,int *cnt1,int *cnt2)
{
	int i,j,k,l,m,n;
	int *six;
	six=(int*)malloc(sizeof(int)*6);
	if(!six)
	{
		printf("����� ��� ������� ������");
		exit(0);
	}
	
	
	*count=0;
	*cnt1=0;
	*cnt2=0;
	for(i=0; i<N-5; i++)
	 for(j=i+1; j<N-4; j++)
	  for(k=j+1; k<N-3; k++)
	   for(l=k+1; l<N-2; l++)
	    for(m=l+1; m<N-1; m++)
	     for(n=m+1; n<N; n++)
	     {
	     	(*count)++;
	     	makesix_array(six,i,j,k,l,m,n,pin);
	     	get_matrix(matrix,six);
	     	if(Check_ev(six,6,x1,x2)==0)
              (*cnt1)++;
            if((Check_ev(six,6,x1,x2)==1) && (Check_sum(six,6,y1,y2))==0)
			  (*cnt2)++; 
			if((Check_ev(six,6,x1,x2)==1) && (Check_sum(six,6,y1,y2))==1)  
			 print(six);
			 
		}
		 
	free(six);	 
	
}
 void get_matrix(int *matrix,int *six)
{
	int i;
	for(i=0; i<6; i++)
	 (*(matrix+ *(six+i)-1))++;
	 
	 
}



void makesix_array(int *six,int i, int j, int k,int l,int m,int n,int *pin)
{
	*(six+0)=*(pin+i);
	*(six+1)=*(pin+j);
	*(six+2)=*(pin+k);
	*(six+3)=*(pin+l);
	*(six+4)=*(pin+m);
	*(six+5)=*(pin+n);
}


void print(int *six)
{
 printf("\n");
 printf("%d %d %d %d %d %d",*(six+0),*(six+1),*(six+2),*(six+3),*(six+4),*(six+5));	
}

int Check_ev(int *pin,int n,int x1,int x2)
{
	int i,cnt=0;
	
	for(i=0; i<n; i++)
	{
		if(*(pin+i)%2==0)
		 cnt++;
	}
	if(cnt>=x1 && cnt<=x2)
	 return 1;
	else
	 return 0; 
	
}

int Check_sum(int *pin,int n,int y1,int y2)
{
	int i,sum=0;
	for(i=0; i<n; i++)
	{
		sum+=*(pin+i);
	}
	if(sum>=y1 && sum<=y2)
	 return 1;
	else
	 return 0; 
	
}

void prinstats(int N,int count,int cnt1,int cnt2,int *matrix)
{
    int i;
	printf("\n\n���������� ����������\n");
	printf("--------------------------------\n");
	printf("�� ������ ��� ��������� %d ������� ��� 6          : %d\n",N,count);
	printf("������ ��� ��� ��������� ��� 1� ���               : %d\n",cnt1);
	printf("������ ��� ��������� ��� 1��� ���� ��� ��� 2���   : %d\n",cnt2);
	printf("������ ��������� ����������                       : %d\n",count-(cnt1+cnt2));
	for(i=0; i<49; i++)
	 printf("\n� ������� %d ����������� �� {%d} ������",i+1,*(matrix+i));
}


