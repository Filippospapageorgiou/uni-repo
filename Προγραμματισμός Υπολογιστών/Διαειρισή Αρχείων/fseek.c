//fseak.c
#include <stdio.h>
#include <stdlib.h>

#define N 10

struct point{
	int x;
	int y;
};



main()
{
	FILE *fp;
	int i;
	struct point data;
	
	fp=fopen("binarydata.dat","rb");
	if(fp==NULL)
	{
		printf("Lathos sto anoigma arxeiou");
		exit(0);
	}
	
	printf("Dwse seimeio(0-9): ");
	scanf("%d",&i);
	fseek(fp,sizeof(struct point)*i,SEEK_SET);
	fread(&data,sizeof(struct point),1,fp);
	
	printf("simeio %d: ",i);
	printf("%d %d\n",data.x,data.y);
	
	fclose(fp);
}
