//Kremala
#include <stdio.h>
#include <string.h>

#define ERROR 7

int main(void)
{
	int i,found,len,error,correct;
	char str[30],ch,hide[30]={0};
	
	
	printf("Enter the secret word: ");
	gets(str);
	
	system("cls");
	for(i=0; i<strlen(str); i++)
	 hide[i]='_';
	 
	error=correct=0;
	
	while(error<ERROR)
	{
		printf("\nEnter the characther: ");
		ch=getchar();
		found=0;
		for(i=0; i<strlen(str); i++)
		{
			if(str[i]==ch)
			{
				hide[i]=ch;
				found=1;
				correct++;
				if(correct==len)
				{
					printf("The secret word is %s",str);
					return 0;
				}
			}
		}
		if(found==0)
		{
			error++;
			printf("\nError %c doesnt exist you got %d attemps.try again",ch,ERROR-error);
		}
		else
		 printf("%s",hide);
	}
	return 0;
	 
}
