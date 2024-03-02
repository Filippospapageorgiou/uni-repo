//fread.c:diabasma dyadikou arxeiou
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
	char c;
	int i;
	struct point data[N];
	
	fp=fopen("binarydata.dat","rb");
	if(fp==NULL)
	{
		printf("Error opening file!");
		exit(0);
	}
	
	//diabsma apo to arxeio
	fread(data,sizeof(struct point),N,fp);
	if(fread==N)
	{
		printf("Error opening binary file!");
		exit(0);
	}
	
	//Ektiposi stin othoni
	for(i=0; i<N; i++)
	 printf("%d %d\n",data[i].x,data[i].y);
	
	fclose(fp);
}
