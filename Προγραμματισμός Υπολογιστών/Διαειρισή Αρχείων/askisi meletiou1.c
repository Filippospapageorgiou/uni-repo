#include <stdio.h>
#include <stdlib.h>



int main(void)
{
	FILE *fp;
	char string[20];
	int count1=0,count2=0;
	int i;
	printf("Dwse to onoma tou arxeiou:");
	gets(string);
	fp=fopen(string,"w");
	if(fp==NULL)
	{
		printf("Error opening file...");
		exit(0);
	}
	i=0;
	while(string[i]!='\0')
	{
		if(string[i]>='A' && string[i]<='Z')
		 count1++;
		else if(!(string[i]>='A' && string[i]<='Z') && string[i]!='\n')
		 count2++; 
		i++;
	}
	fprintf(fp,"To sinoliko plithos kefalaion einai : %d\n",count1);
	fprintf(fp,"To sinoliko plithos pou den einai kefalaia i allagi grammis einai: %d",count2);
	fclose(string);
	
	
	
	
}
