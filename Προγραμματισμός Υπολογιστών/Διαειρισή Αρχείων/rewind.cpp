//rewind.c
#include <stdio.h>
#include <stdlib.h>

main()
{
	FILE *fp;
	char c;
	int i;
	
	fp=fopen("test.txt","r");
	if(fp==NULL)
	{
		printf("Lathos sto anoigma arxeiou");
		exit(0);
	}
	
	for(i=0; i<5; i++)
	{
		printf("%c",fgetc(fp));
	}
	printf("\n");
	
	rewind(fp);
	
	while((c=fgetc(fp))!=EOF)
	 printf("%c",c);
	 
	 fclose(fp);
}
