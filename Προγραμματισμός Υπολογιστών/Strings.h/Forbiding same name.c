#include <stdio.h>
#include <string.h>

#define ROWS 10
#define COLS 50

int main(void)
{
	int i,j,flag,len;
	char string[ROWS][COLS];
	system("chcp 1253");
	printf("***Καταχώρηση ονομάτων τάξης***");
	printf("-------------------------------\n");
	
	for(i=0; i<ROWS; i++)
	{
		do{
			flag=i;
			printf("Δώσε %d_Ονομα-> ",i+1);
			gets(string[i]);
			for(j=0; j<ROWS; j++)
			{
				if(flag!=j)
				{
					len=strcmp(string[flag],string[j]);
				}
			}
		}while(len==0);
	}
	
}
