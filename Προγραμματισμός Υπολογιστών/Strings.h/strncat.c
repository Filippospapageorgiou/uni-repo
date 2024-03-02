// strncat.c:

#include <stdio.h>
#include <string.h>

#define N 80

main()
{
	int i;
	char str1[N],str2[N];
	
	printf("Dwse tin simvoloseira 1: ");
	gets(str1);
	printf("Dwse tin simvoloseira 2: ");
	gets(str2);
	
	for(i=1; i<=5; i++)
	{
		strncat(str1,str2,i);
		printf("\nstr1=%s",str1);
	}
}
