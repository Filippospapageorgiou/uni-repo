#include <stdio.h>
#include <stdlib.h>

main()
{
	FILE *fp;
	
	fp=fopen("temp.txt","w");
	if(!fp)
	{
		printf("Lahtos");
		exit(0);
	}
	fprintf(fp,"0123456789");
	fclose(fp);
	
	fp=fopen("temp.txt","a+");
	printf("Position=%d",ftell(fp));
	
	fprintf(fp,"XXXX");
	
	rewind(fp);
	while(!feof(fp))
	{
		printf("%c",fgetc(fp));
	}
	
	
	fclose(fp);
}
