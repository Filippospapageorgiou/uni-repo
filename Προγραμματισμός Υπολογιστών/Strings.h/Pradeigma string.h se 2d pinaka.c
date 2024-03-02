#include <stdio.h>
#include <string.h>

main()
{
	char s[10][20];
	int i,j;
	
	for(i=0; i<10; i++)
	{
		printf("Dwse %d-o frasi-> ",i+1);
		gets(s[i]);
	}
	for(i=0; i<10; i++)
	{
		puts(s[i]);
	}
	putchar(s[3][2]); //emfanizei ton 3 xaraktira tis 4 fraseis
	for(i=0; i<10; i++)
	 putchar(s[i][0]); //emfanizei ton 1 xaraktirs ka8e fraseis
	putchar('\n');
	for(i=strlen(s[5])-1; i>=0; i--) //emfanizei antistrofa tous xaraktires tis 5is fraseis
	{
		putchar(s[5][i]);
	}
	putchar('\n');
	for(i=0; i<10; i++)
	{
		putchar(s[i][strlen(s[i])-1]); //emfanizei ton teleutai xaraktira k8e fraseis
	}
	putchar('\n');
	for(i=0; i<10; i++)
	{
		for(j=0; j<strlen(s[i]); j++)
		{
			if(s[i][j]>='0' && s[i][j]<='9' )// antika8ista ka8e arithmitkko apo to 0-9 me tin '-'
			 s[i][j]='-';
		}
	}
	for(i=0; i<10; i++)
	{
		puts(s[i]);
	}
	
	 
}
