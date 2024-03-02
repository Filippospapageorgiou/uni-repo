 /* Υλοποιείστε τις παρακάτω συναρτήσεις:
 * -strdup
 * -strlwr
 * -strupr
 */
 
#include <stdio.h>
#include <string.h>

void mystrdup(char [],char []);
void mystrlwr(char str[]);
void mystrupr(char str[]); 
 
int main(void)
{
	char str[100],str2[100];
	
	printf("Dwse simvoloseira: ");
	scanf("%s",str);
	mystrdup(str,str2);
	printf(" STRDUP: {I simvoloseira %s antigraf8ike stin %s}\n",str,str2);
	mystrlwr(str);
	printf("\n STRLWR:  {%s}",str);
	mystrupr(str);
	printf("\nSTRUPR:   {%s}",str);

}
//antigrafi simvoloseirtas
void mystrdup(char str[],char str2[])
{
	int i;
	i=0;
	while(str[i]!='\0')
	{
		str2[i]=str[i];
		i++;
	}
	
	str2[i+1]='\0';
}

//apo kefalaia se mikra
void mystrlwr(char str[])
{
	int i;
	i=0;
	while(str[i]!='\0')
	{
		if(str[i]>='A' && str[i]<='Z')
		{
			str[i]=str[i]+32;
		}
		i++;
	}
}


void mystrupr(char str[])
{
	int i=0;
	while(str[i]!='\0')
	{
		if(str[i]>='a' && str[i]<='z')
		 str[i]=str[i]-32;
		i++;
	}
}


