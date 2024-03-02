//strtok.c

#include <stdio.h>
#include <string.h>
#define N 80
main()
{
	int i,res;
	char str[N],*p;
	
	printf("Dwse ti simvoloseira: ");
	gets(str);
	//Xorismos me tin strtok
	p=strtok(str," ,.");
	while(p!=NULL)
	{
		printf("%s\n",p);
		p=strtok(NULL," ,.");
	}
}
