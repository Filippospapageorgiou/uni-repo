/*fprintf.cpp Grapsimo arxeio */
#include <stdio.h>
#include <stdlib.h>


main()
{
	FILE *fp;
	int x=1;
	
	//Anoigma arxeiou
	fp=fopen("test.txt","w");
	if(fp==NULL)
	{
		printf("Error on opening file!!");
		exit(0);
	}
	
	//Grapsimo se arxeio
	fprintf(fp,"Mia grammi\n");
	fprintf(fp,"Kai kapoioi arithmoi: %d %d %d",x,x*5,x/2);
	
	//kleisimo arxeiou
	fclose(fp);
}
