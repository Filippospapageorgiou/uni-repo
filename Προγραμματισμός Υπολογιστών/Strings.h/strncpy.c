//strncpy.c

#include <stdio.h>
#include <string.h>

#define N 80

main()
{
	char str1[N],str2[N];
	int l=5;
	
	printf("Dwse ti simvoloseira: ");
	gets(str1);
	
	strncpy(str2,str1,l);
	
	printf("str1=%s, str2=%s",str1,str2);
}
