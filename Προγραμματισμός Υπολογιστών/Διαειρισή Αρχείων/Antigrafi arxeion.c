//Antigrafi arxeiou se neo arxeio
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;
	FILE *fTO;
	char str[80];
	char str2[80];
	
	
	printf("Dwse to arxeio pou 9es na antigrapsies: ");
	scanf("%s",str);
	
	fp=fopen(str,"r");
	if(!fp)
	{
		printf("Lathos sto anoigma arxeio den iparxei");
		exit(0);
	}
	
	
	printf("Dwse to neo arxeio: ");
	scanf("%s",str2);
	
	fTO=fopen(str2,"r");
	if(fTO)
	{
		printf("To arxeio iparxei idi");
		exit(0);
	}
	fclose(fTO);
	
	fTO=fopen(str2,"w+");
	if(!fTO)
	{
		printf("To arxeio iparxei idi");
		exit(0);
	}
	
	while(!feof(fp))
	 fputc(fgetc(fp),fTO);
	 
	 fclose(fp);
	 fclose(fTO);
	 
	return 0; 
}
