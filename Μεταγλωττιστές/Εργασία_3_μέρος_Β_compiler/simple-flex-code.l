%option  noyywrap

%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Header file pou periexei lista me ola ta tokens */
#include "simple-bison-code.tab.h"

/* Orismos metrhth trexousas grammhs */

void prn(char *s);

extern char *yytext;
int lex_warn=0;

/* Στο παρακάτω τμήμα του κώδικα, οριζούμε τα tokens που θα χρησιμοποιηθούν και αναφέρονται στο simple-bison-code.tab.h αρχείο, με την αντίστοιχη Κανονική Εκφραση. 
  Τέλος,τροποποιήσαμε και μερικές απο τις κανονικές εκφράσεις που είχαμε βάλει στο Α μέρος της εργασίας, καθώς παρουσιάστηκαν σφάλματα κατα την διάρκεια της εκτέλεσης του simple-bison κώδικα. 
*/

%}

DELIMITER       [ \t]+
DECIMAL        	([0]|([1-9][0-9]*))
BINARY			[0][b|B][01]+
FLOAT			(([1-9][0-9]*)|0)(\.[0-9]+)?([eE][-+]?[0-9]+)?
IMAGINARY		[+-]?(0(\.[0-9]+)+|[1-9][0-9]*(\.[0-9]+)?)([eE][+-]?[0-9]+)?[j]
IDENTIFIER		[a-zA-Z_][a-zA-Z0-9_]*
STRING 			(\"(\\[\\\"'nr]|[^\n\"'\\])*\")|(\'(\\[\\\"'nr]|[^\n\"'\\])*\')
COMMENT			#.*
KEYWORD 		False|class|finally|is|return|None|continue|for|lambda|try|True|def|from|nonlocal|while|and|del|global|not|with|as|elif|if|or|yield|assert|else|import|pass|break|except|in|raise
S_WORD			\(|\)|\[|\]|\{|\}|,|:|\.|;|@|=|->|\+=|\-=|\*=|\/=|\/\/=|%=|@=|&=|\|=|\^=|>>=|<<=|\*\*=
UNKNOWN_TOKEN   .


 /* Στην συνέχεια, ακολουθεί η περιοχή ορισμού των κανόνων που θα υπάρχουν κατα την μεταγλώττιση , δήλαδή τι ενέργειες θα πραγματοποιηθούν με την ανίχνευση περιεχομένου του αρχείου. */
 /* Την περίπτωση των operator την χωρίσαμε για κάθε operator ξεχωριστά ενώ προσθέσαμε τις λέξεις print,len και το TOKEN_ERROR για αναγνώριση λαθών */
%x error

%%
"+" 	{ return PLUS; }
"*" 	{ return TIMES; }
"/" 	{ return DIVIDE; }
"^"	 { return POWER; }
"%" 	{ return MOD; }
">" 	{ return GREATER; }
"<" 	{ return LESS; }
">=" 	{ return GREATER_EQ; }
"<=" 	{ return LESS_EQ; }
"==" 	{ return EQUAL; }
"!=" 	{ return NOT_EQUAL; }

"(" 	{ return LEFT_PAREN; }
")" 	{ return RIGHT_PAREN; }
"["		{ return LS_BRACKET; }
"]"		{ return RS_BRACKET; }
"{"		{ return L_BRACKET; }  
"}"		{ return R_BRACKET; }
","		{ return COMMA; }
":"		{ return COLON; }
"."		{ return DOT; }
";"		{ return SEMICOLON; }
"="		{ return ASSIGN; }
"+="	{ return ADD_ASSIGN; }
"-="	{ return SUB_ASSIGN; }
"*="	{ return MULT_ASSIGN; }
"/="    { return DIV_ASSIGN; }

"print" { return PRINT; }
"len"   { return LEN; }


{DELIMITER}     {  }
{KEYWORD}		{ yylval.sval = strdup(yytext); return KEYWORD; }
{S_WORD}		{ return S_WORD; }
{DECIMAL}      	{ yylval.ival = atoi(yytext); return DECIMAL; }
{BINARY}		{ yylval.sval = strdup(yytext); return BINARY; }
{FLOAT}			{ yylval.fval = atof(yytext); return FLOAT; }
{IMAGINARY}		{ yylval.sval = strdup(yytext); return IMAGINARY; }
{IDENTIFIER}	{ yylval.sval = strdup(yytext); return IDENTIFIER; }
{STRING}		{ yylval.sval = strdup(yytext); return STRING; }
{COMMENT}		{ return COMMENT; }

"-" 			{ return MINUS; }

\n              { return NEWLINE; }

.               { lex_warn++; BEGIN(error); return TOKEN_ERROR; }
<error>[ \t]+   { BEGIN(0); printf("\n\t\t%d character(s) ignored so far\n",lex_warn); }
<error>.        { lex_warn++; }
<error>\n       { BEGIN(0); printf("\n\t\t%d character(s) ignored so far\n",lex_warn); return NEWLINE; }


%%

void prn(char *s){
    printf("\tFlex->Matched token:%s\n",yytext);
}
