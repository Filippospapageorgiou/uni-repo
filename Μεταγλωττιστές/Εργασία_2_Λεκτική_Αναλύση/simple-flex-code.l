%option noyywrap


%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "token.h"


int line = 1;

%}


DELIMITER       [ \t]+
INTEGER         -?[0-9]+|0[xX][0-9A-Fa-f]+|0[0-7]*
FLOAT           [+-]?([0-9]*[.])?[0-9]+([eE][+-]?[0-9]+)?
KEYWORD         break|do|if|sizeof|case|double|int|struct|func|else|long|switch|const|float|return|void|continue|for|short|while
OPERATOR        \/=|\*=|\-=|\+=|>=|<=|\+|\-|\*|\/|%|==|!=|<|>|&&|\|\||!|&|=
IDENTIFIER      ([A-Za-z_][A-Za-z_0-9]+)
STRING          \"([^"\\]|\\[\\n"\\])*\" 
COMMENT          \/\/.*|\/\*(.|\n)*?\*\/
UNKNOWN_TOKEN   .


%%

{DELIMITER}     { printf("Matched DELIMITER: '%s'\n", yytext); return DELIMITER; }
{INTEGER}       { printf("Matched INTEGER: %s\n", yytext); return INTEGER; }
{FLOAT}         { printf("Matched FLOAT: %s\n", yytext); return FLOAT; }
{KEYWORD}       { printf("Matched KEYWORD: %s\n", yytext); return KEYWORD; }
{OPERATOR}      { printf("Matched OPERATOR: %s\n", yytext); return OPERATOR; }
{IDENTIFIER}    { printf("Matched IDENTIFIER: %s\n", yytext); return IDENTIFIER; }
{STRING}        { printf("Matched STRING: \"%s\"\n", yytext); return STRING; }
{COMMENT}       { printf("Matched COMMENT: '%s'\n", yytext); }
{UNKNOWN_TOKEN} { printf("Line=%d, UNKNOWN_TOKEN, value=\"%s\"\n", line, yytext); }
\n              { line++; printf("\n"); }
<<EOF>>         { printf("#END-OF-FILE#\n"); exit(0); }

%%


char *tname[8] = {"DELIMITER","INTEGER","FLOAT","KEYWORD","OPERATOR","IDENTIFIER","STRING","COMMENT"};


int main(int argc, char **argv){
        int token;

        if(argc == 3){
                if(!(yyin = fopen(argv[1], "r"))) {
                        fprintf(stderr, "Cannot read file: %s\n", argv[1]);
                        return 1;
                }
                if(!(yyout = fopen(argv[2], "w"))) {
                        fprintf(stderr, "Cannot create file: %s\n", argv[2]);
                        return 1;
                }
        }
        else if(argc == 2){
                if(!(yyin = fopen(argv[1], "r"))) {
                        fprintf(stderr, "Cannot read file: %s\n", argv[1]);
                        return 1;
                }
        }

        FILE *outputFile = fopen("output.txt", "w");
        if (!outputFile) {
          fprintf(stderr, "Cannot create output file: output.txt\n");
          return 1;
        }


        while( (token=yylex()) >= 0){
            if((token != 8)&&(token !=1)){
                 fprintf(outputFile, "\tLine=%d, token=%s, value=\"%s\"\n", line, tname[token-1], yytext);
              }
        }
        return 0;
}
