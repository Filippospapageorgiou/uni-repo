//strncmp.c

#include <stdio.h>
#include <string.h>

#define N 80

main()
{
	int res,l=4;
	char str1[N],str2[N];
	
	printf("Dwse tin 1 simvoloseira: ");
	gets(str1);
	printf("Dwse tin 2 simvoloseira: ");
	gets(str2);
	//sikgrisi me tin strncmp
	res=strncmp(str1,str2,l);
	
	if(res<0)
	 printf("str1<str2 (res=%d)",res);
	else if(res==0)
	 printf("str1=str2 (res=%d)",res);
	else
	 printf("str1>str2 (res=%d)",res);
}
