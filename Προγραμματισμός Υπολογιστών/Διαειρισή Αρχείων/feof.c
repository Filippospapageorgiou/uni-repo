//feof.c:deixnei tin xrisi tis
#include <stdio.h>
#include <stdlib.h>

main()
{
	char c;
	FILE *fp;
	fp=fopen("test.txt","r");
	if(fp==NULL){
		printf("Error opening file");
		exit(0);
	}
	
	while(!feof(fp))
	{
		c=fgetc(fp);
		printf("%c",c);
	}
	fclose(fp);
}
