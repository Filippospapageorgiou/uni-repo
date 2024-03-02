//fscanf.c:deixnei tin leitourgia tis fscanf
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
	int n;//plithos eggrafwn
	struct point points[N]; //Eggarfes
	
	fp=fopen("points.txt","r");
	if(fp==NULL)
	{
	  printf("Lathos sto anoigma arxeiou");
	  exit(0);
	}
	
	fscanf(fp, "%d", &n);
	for(i=0; i<n; i++)
	  fscanf(fp,"%d %d ",&points[i].x,&points[i].y);
	
	fclose(fp);
	for(i=0; i<n; i++)
	 printf(fp,"%d %d\n",points[i].x,points[i].y);

	
}
