//strcpy.c:Antigrafi mias simvoloseiras

#include <stdio.h>
#include <string.h>
#define s 50

main()
{
	char str1[s],str2[s],str3[s];
	int choice;
	
	printf("Dwse tin 1h simvoloseira: ");
	gets(str1);
	printf("Dwse tin 2h simvoloseira: ");
	gets(str2);
	
	do{
		printf("\n\nPoia simvoloseira 8es na antigrapsris [1-2]: ");
		scanf("%d",&choice);
	}while(choice!=1 && choice!=2);
	if(choice==1)
	{
		strcpy(str3,str1);
	}
	else if(choice==2)
	{
		strcpy(str3,str2);
	}
	printf("\n");
	puts(str1);
	puts(str2);
	puts(str3);
	
}
