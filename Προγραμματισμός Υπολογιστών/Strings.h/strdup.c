//strdup.c

#include <stdio.h>
#include <string.h>

#define N 80

main()
{
	char str[N];
	char *str2;
	
	printf("Dwse tin simvoloseira: ");
	gets(str);
	str2=strdup(str);
	if(!str2)
	{
		printf("apotixia desmeusi mnimis..");
		exit(0);
	}
	else{
		printf("Antigrafike: %s me mikos: %d",str2,strlen(str2));
	}
}
