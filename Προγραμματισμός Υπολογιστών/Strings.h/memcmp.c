//memcmp.c:deixnei in xrisi tis memcpy
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
	char str1[]={'a','b','c','\0','d','e'};
	char str2[]={'a','b','c','\0','d','f'};
	
	
	if(strcmp(str1,str2)==0)
	 printf("same\n");
	else
	 printf("diffrent\n");
	 
	
	if(memcmp(str1,str2,sizeof(str1))==0)
	 printf("same");
	else
	 printf("Diffrent");   
}
