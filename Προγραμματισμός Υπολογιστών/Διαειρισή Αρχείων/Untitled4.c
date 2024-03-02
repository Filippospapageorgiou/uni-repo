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
	
	fp=fopen("temp.txt","r+");
	printf("Position=%ld\n",ftell(fp));
	while(!feof(fp))
	  printf("%c",fgetc(fp));
	  
	printf("Position=%ld\n",ftell(fp));
	
	rewind(fp);
	fprintf(fp,"OOOO");
	rewind(fp);
	while(!feof(fp))
	  printf("%c",fgetc(fp));
	  
	
	  
	
	
	
	fclose(fp);
}
