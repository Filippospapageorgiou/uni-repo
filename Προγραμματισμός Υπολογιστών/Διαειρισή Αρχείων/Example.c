#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;
	int i,arr;
	fp=fopen("Tyxaioi.txt","r");
	if(fp==NULL)
	{
		puts("Error opening file!");
		exit(2);
	}
	
	for(i=0; i<150; i++)
	{
		fscanf(fp,"%d",&arr);
		printf("%d\n",arr);
		if(feof(fp))
		 break;
	}
	fclose(fp);
}
