//Paradeigma xrisis simvoloseirm

#include <stdio.h>
#include <string.h>

main()
{
	char lex[30],ans[30];
	strcpy(lex,"POLITISMIKI"); //Kataxorizei tin lexi poli.. srin simvoloseira lex
	printf("Mikos lex=%d\n",strlen(lex)); //mikos simvoloseiras
	strcat(lex," "); //Pros8etei sto telos tis lex ena keno
	strcat(lex,"TEXNOLOGIA");
	puts(lex);
	printf("Mikos lex=%d\n",strlen(lex));
	printf("Dwse ena tmima tou aigiou: ");
	gets(ans);
	if(strcmp(lex,ans)==0) //Elenxei an einai idies
	 printf("Eiai dikos mas");
	else if(strstr(lex,ans)!=NULL) //Elenxei an i frasi ans periexetai mesa stin lex
	 printf("Eisia misos dikos mas");
	else
	 printf("Atixises");
	printf("\n");
	puts(strcpy(lex,"TELOS"));   
	
}
