//strcmp.c: sikgrinei dio simvoloseires

#include <stdio.h>
#include <string.h>
#define s 50

main()
{
	char str1[s],str2[s];
	int len;
	
	printf("Dwse tin 1h prwti simvoloseira: ");
	gets(str1);
	printf("Dwse tin 2h deuteri  seimvoloseira: ");
	gets(str2);
	len=strcmp(str1,str2);
	
	if(len==-1)
	 printf("I 1h simvoloseira einai megaliteri tis 2hs");
	else if(len==0)
	 printf("Einai ises");
	else if(len==1)
	  printf("I 2h simvoloseira einai megaliteri tis 1hs");
	 
	
}
