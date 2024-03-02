// strlen.c:Epistrefei to plithos xaraktirwn simvoloseiras

#include <stdio.h>
#include <string.h>

main()
{
	char *pp,lexi[40];
	int len;
	
	pp="skoulikomimirmigkotripa";
	len=strlen(pp);
	printf("i leji %s exei %d xaraktires\n",pp,len);
	printf("Dwse mia lexi: ");
	gets(lexi);
	len=strlen(lexi);
	printf("i leji %s exei %d xaraktires\n",lexi,len);
	printf("%d\n",strlen("telos"));
	
}
