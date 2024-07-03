%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include  <string.h>

extern FILE *yyin;
extern FILE *yyout;

int yylex(void);
void yyerror(const char*);

/* Μετρητές σωστών και λανθασμένων εκφράσεων και λέξεων */
static int errors=0;
static int par_warn = 0;
static int correct = 0;
static int correct_words = 0;

#define YYDEBUG 1

/* Συναρτήσεις για μετατροπή από int,float σε string */
char* int_to_string(int num) {
    char* str = malloc(12 * sizeof(char));  
    sprintf(str, "%d", num);
    return str;
}

char* float_to_string(float num) {
    char* str = malloc(20 * sizeof(char)); 
    sprintf(str, "%.2f", num);
    return str;
}

/* Συνάρτηση για επιστρογή μεγέθους λίστας-πλειάδας */
int getListSize(const char* string) {
    char* copy = strdup(string);  
    int count = 0;
    char* token = strtok(copy, ",");
    while (token != NULL) {
        count++;
        token = strtok(NULL, ",");
    }
    free(copy);  
    return count;
}

/* Συνάρτηση για συνένωση λίστας-πλειάδας */
char* concatWithComma(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t commaLen = strlen(", ");    
    char* result = (char*)malloc((len1 + len2 + commaLen + 1) * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    strcpy(result, str1);
    strcat(result, ", ");
    strcat(result, str2);
    return result;
}
%}

/* Δήλωση union για τον ορισμό διαφορετικών τύπων δεδομένων για τα αντίστοιχα tokens */
%union {
  int 	ival;
  float fval;
  char 	*sval;
}

/* Ορισμός των αναγνωριστικών λεκτικών μονάδων */
%token <ival> DECIMAL LEN
%token <fval> FLOAT
%token <sval> STRING BINARY IMAGINARY IDENTIFIER KEYWORD PRINT

%token S_WORD UNKNOWN_TOKEN COMMENT
%token PLUS MINUS TIMES DIVIDE POWER MOD GREATER LESS GREATER_EQ LESS_EQ EQUAL NOT_EQUAL
%token LEFT_PAREN RIGHT_PAREN LS_BRACKET RS_BRACKET L_BRACKET R_BRACKET COMMA COLON DOT SEMICOLON ASSIGN ADD_ASSIGN SUB_ASSIGN MULT_ASSIGN DIV_ASSIGN
%token TOKEN_ERROR NEWLINE

/* Ορισμός προτεραιοτήτων των tokens */
%left 	ASSIGN
%left 	PLUS MINUS
%left 	TIMES DIVIDE MOD 
%left 	NEG
%right 	POWER
%left 	GREATER LESS GREATER_EQ LESS_EQ EQUAL NOT_EQUAL
%left   LS_BRACKET RS_BRACKET L_BRACKET R_BRACKET
%left 	LEFT_PAREN RIGHT_PAREN

%type<ival> dec_expr
%type<fval> float_expr
%type<sval> string_expr
%type<sval> list_expr list_types

%%

| IDENTIFIER ASSIGN INTEGER { $$ = $1; }

/* Ορισμός των γραμματικών κανόνων, εκτέλεση του ανάλογου κώδικα και αύξηση των κατάλληλων μετρητών */
program:
		| program expr;
        ;
expr:
		dec_expr NEWLINE 			{  fprintf(yyout,"%d\n", $1); correct++; }
		| float_expr NEWLINE 		{ fprintf(yyout,"%.2f\n", $1); correct++; }
        | string_expr NEWLINE 		{ fprintf(yyout,"%s\n", $1); correct++; }
		| list_expr  NEWLINE 		{ fprintf(yyout,"%s\n", $1); correct++; }
		| COMMENT NEWLINE 			{ }
		| NEWLINE					{ }
		| TOKEN_ERROR				{ errors++; }
		;		
dec_expr:
        DECIMAL         						{ $$ = $1; correct_words++; }
        | dec_expr PLUS dec_expr			    { $$ = $1 + $3; correct_words++; }
		| dec_expr MINUS dec_expr  	 		    { $$ = $1 - $3; correct_words++; }
		| dec_expr TIMES dec_expr  			    { $$ = $1 * $3; correct_words++; }
		| dec_expr DIVIDE dec_expr 		    	{ $$ = $1 / $3; correct_words++; }
		| dec_expr MOD dec_expr  		        { $$ = $1 % $3; correct_words++; }
		| dec_expr POWER dec_expr    	        { $$ = pow($1, $3); correct_words++; }
		| dec_expr GREATER dec_expr             { $$ = ($1 > $3) ? 1 : 0; correct_words++; }
		| dec_expr LESS dec_expr                { $$ = ($1 < $3) ? 1 : 0; correct_words++; }
		| dec_expr GREATER_EQ dec_expr          { $$ = ($1 >= $3) ? 1 : 0; correct_words++; }
		| dec_expr LESS_EQ dec_expr             { $$ = ($1 <= $3) ? 1 : 0; correct_words++; }
		| dec_expr EQUAL dec_expr               { $$ = ($1 == $3) ? 1 : 0; correct_words++; }
		| dec_expr NOT_EQUAL dec_expr           { $$ = ($1 != $3) ? 1 : 0; correct_words++; }
		| LEFT_PAREN dec_expr RIGHT_PAREN  		{ $$ = $2; correct_words+=2; }
		| MINUS dec_expr %prec NEG 				{ $$ = -$2; correct_words++; }
		| LEN LEFT_PAREN list_expr RIGHT_PAREN	{ $$ = getListSize($3); correct_words+=3; }	
		
		/* Λάθος περιπτώσεις */
		|DECIMAL DECIMAL 								{printf("\tWarning!Integer starting with 0!\n");par_warn++; $$=$2;}
		|DECIMAL IDENTIFIER 							{printf("\tWarning!Identifier starting with number!\n");par_warn++; }
		|DECIMAL DOT 									{printf("\tWarning!Incomplete number!\n");par_warn++; }
		|DOT DECIMAL 									{printf("\tWarning!Incomplete number!\n");par_warn++; }
		|dec_expr TOKEN_ERROR PLUS dec_expr			    {printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$=$1+$4;}
		|dec_expr TOKEN_ERROR MINUS dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = $1 - $4;}
		|dec_expr TOKEN_ERROR TIMES dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = $1 * $4;}
		|dec_expr TOKEN_ERROR DIVIDE dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++;$$ = $1 / $4;}
		|dec_expr TOKEN_ERROR MOD dec_expr			    {printf("\tWarning!Unknown operator ignored!\n");par_warn++;$$ = $1 % $4;}
		|dec_expr TOKEN_ERROR POWER dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = pow($1, $4);}
        |dec_expr TOKEN_ERROR GREATER dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 > $4) ? 1 : 0;}
        |dec_expr TOKEN_ERROR LESS dec_expr			    {printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 < $4) ? 1 : 0;}
        |dec_expr TOKEN_ERROR GREATER_EQ dec_expr		{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 >= $4) ? 1 : 0;}
        |dec_expr TOKEN_ERROR LESS_EQ dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++;$$ = ($1 <= $4) ? 1 : 0; }
        |dec_expr TOKEN_ERROR EQUAL dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 == $4) ? 1 : 0;}
        |dec_expr TOKEN_ERROR NOT_EQUAL dec_expr		{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 != $4) ? 1 : 0;}
        
        |dec_expr PLUS TOKEN_ERROR dec_expr			    {printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$=$1+$4;}
		|dec_expr MINUS TOKEN_ERROR dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = $1 - $4;}
		|dec_expr TIMES TOKEN_ERROR  dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = $1 * $4;}
		|dec_expr DIVIDE TOKEN_ERROR dec_expr		    {printf("\tWarning!Unknown operator ignored!\n");par_warn++;$$ = $1 / $4;}
		|dec_expr MOD TOKEN_ERROR  dec_expr			    {printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = $1 % $4;}
		|dec_expr POWER TOKEN_ERROR  dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = pow($1, $4);}
        |dec_expr GREATER TOKEN_ERROR  dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 > $4) ? 1 : 0;}
        |dec_expr LESS TOKEN_ERROR  dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 < $4) ? 1 : 0;}
        |dec_expr GREATER_EQ TOKEN_ERROR  dec_expr	    {printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 >= $4) ? 1 : 0;}
        |dec_expr LESS_EQ TOKEN_ERROR  dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++;$$ = ($1 <= $4) ? 1 : 0; }
        |dec_expr EQUAL TOKEN_ERROR  dec_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 == $4) ? 1 : 0;}
        |dec_expr NOT_EQUAL TOKEN_ERROR  dec_expr	    {printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 != $4) ? 1 : 0;}
        
        |dec_expr PLUS PLUS dec_expr                    {printf("\tWarning:Consecutive use of operator!\n");par_warn++; $$=$1+$4;}
		|dec_expr TIMES TIMES dec_expr			        {printf("\tWarning!Consecutive use of operator!!\n");par_warn++; $$ = $1 * $4;}
		|dec_expr DIVIDE DIVIDE dec_expr			    {printf("\tWarning!Consecutive use of operator!!\n");par_warn++;$$ = $1 / $4;}
		|dec_expr MOD MOD dec_expr			            {printf("\tWarning!Consecutive use of operator!\n");par_warn++;$$ = $1 % $4;}
		|dec_expr POWER POWER dec_expr			        {printf("\tWarning!Consecutive use of operator!!\n");par_warn++; $$ = pow($1, $4);}
        |dec_expr GREATER GREATER dec_expr			    {printf("\tWarning!Consecutive use of operator!\n");par_warn++; $$ = ($1 > $4) ? 1 : 0;}
        |dec_expr LESS LESS dec_expr			        {printf("\tWarning!Consecutive use of operator!\n");par_warn++; $$ = ($1 < $4) ? 1 : 0;}
        |dec_expr GREATER_EQ GREATER_EQ dec_expr		{printf("\tWarning!Consecutive use of operator!\n");par_warn++; $$ = ($1 >= $4) ? 1 : 0;}
        |dec_expr LESS_EQ LESS_EQ dec_expr			    {printf("\tWarning!Consecutive use of operator!\n");par_warn++;$$ = ($1 <= $4) ? 1 : 0; }
        |dec_expr EQUAL EQUAL dec_expr			        {printf("\tWarning!Consecutive use of operator!\n");par_warn++; $$ = ($1 == $4) ? 1 : 0;}
        |dec_expr NOT_EQUAL NOT_EQUAL dec_expr		    {printf("\tWarning!Consecutive use of operator!\n");par_warn++; $$ = ($1 != $4) ? 1 : 0;} 
		;
float_expr:
        FLOAT         							{ $$ = $1; correct_words++; }
        | float_expr PLUS float_expr			{ $$ = $1 + $3; correct_words++; }
		| float_expr MINUS float_expr  	 		{ $$ = $1 - $3; correct_words++; }
		| float_expr TIMES float_expr  			{ $$ = $1 * $3; correct_words++; }
		| float_expr DIVIDE float_expr 		  	{ $$ = $1 / $3; correct_words++; }
		| float_expr POWER float_expr    	    { $$ = pow($1, $3); correct_words++; }
		| float_expr GREATER float_expr         { $$ = ($1 > $3) ? 1 : 0; correct_words++; }
		| float_expr LESS float_expr            { $$ = ($1 < $3) ? 1 : 0; correct_words++; }
		| float_expr GREATER_EQ float_expr      { $$ = ($1 >= $3) ? 1 : 0; correct_words++; }
		| float_expr LESS_EQ float_expr         { $$ = ($1 <= $3) ? 1 : 0; correct_words++; }
		| float_expr EQUAL float_expr           { $$ = ($1 == $3) ? 1 : 0; correct_words++; }
		| float_expr NOT_EQUAL float_expr       { $$ = ($1 != $3) ? 1 : 0; correct_words++; }
		| LEFT_PAREN float_expr RIGHT_PAREN 	{ $$ = $2; correct_words+=2; }
		| MINUS float_expr %prec NEG 			{ $$ = -$2; correct_words++; }
		
		/* Λάθος περιπτώσεις */
		|float_expr TOKEN_ERROR PLUS float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$=$1+$4;}
		|float_expr TOKEN_ERROR MINUS float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = $1 - $4;}
		|float_expr TOKEN_ERROR TIMES float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = $1 * $4;}
		|float_expr TOKEN_ERROR DIVIDE float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++;$$ = $1 / $4;}
		|float_expr TOKEN_ERROR POWER float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = pow($1, $4);}
        |float_expr TOKEN_ERROR GREATER float_expr		{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 > $4) ? 1 : 0;}
        |float_expr TOKEN_ERROR LESS float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 < $4) ? 1 : 0;}
        |float_expr TOKEN_ERROR GREATER_EQ float_expr		{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 >= $4) ? 1 : 0;}
        |float_expr TOKEN_ERROR LESS_EQ float_expr	    {printf("\tWarning!Unknown operator ignored!\n");par_warn++;$$ = ($1 <= $4) ? 1 : 0; }
        |float_expr TOKEN_ERROR EQUAL float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 == $4) ? 1 : 0;}
        |float_expr TOKEN_ERROR NOT_EQUAL float_expr		{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 != $4) ? 1 : 0;}
        
        |float_expr PLUS TOKEN_ERROR float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$=$1+$4;}
		|float_expr MINUS TOKEN_ERROR float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = $1 - $4;}
		|float_expr TIMES TOKEN_ERROR  float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = $1 * $4;}
		|float_expr DIVIDE TOKEN_ERROR float_expr		    {printf("\tWarning!Unknown operator ignored!\n");par_warn++;$$ = $1 / $4;}
		|float_expr POWER TOKEN_ERROR  float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = pow($1, $4);}
        |float_expr GREATER TOKEN_ERROR  float_expr       {printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 > $4) ? 1 : 0;}
        |float_expr LESS TOKEN_ERROR  float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 < $4) ? 1 : 0;}
        |float_expr GREATER_EQ TOKEN_ERROR  float_expr	{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 >= $4) ? 1 : 0;}
        |float_expr LESS_EQ TOKEN_ERROR  float_expr	    {printf("\tWarning!Unknown operator ignored!\n");par_warn++;$$ = ($1 <= $4) ? 1 : 0; }
        |float_expr EQUAL TOKEN_ERROR  float_expr			{printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 == $4) ? 1 : 0;}
        |float_expr NOT_EQUAL TOKEN_ERROR  float_expr	    {printf("\tWarning!Unknown operator ignored!\n");par_warn++; $$ = ($1 != $4) ? 1 : 0;}
        
        |float_expr PLUS PLUS float_expr                  {printf("\tWarning:Consecutive use of operator!\n");par_warn++; $$=$1+$4;}
		|float_expr TIMES TIMES float_expr			    {printf("\tWarning!Consecutive use of operator!!\n");par_warn++; $$ = $1 * $4;}
		|float_expr DIVIDE DIVIDE float_expr			    {printf("\tWarning!Consecutive use of operator!!\n");par_warn++;$$ = $1 / $4;}
		|float_expr POWER POWER float_expr			    {printf("\tWarning!Consecutive use of operator!!\n");par_warn++; $$ = pow($1, $4);}
        |float_expr GREATER GREATER float_expr			{printf("\tWarning!Consecutive use of operator!\n");par_warn++; $$ = ($1 > $4) ? 1 : 0;}
        |float_expr LESS LESS float_expr			        {printf("\tWarning!Consecutive use of operator!\n");par_warn++; $$ = ($1 < $4) ? 1 : 0;}
        |float_expr GREATER_EQ GREATER_EQ float_expr		{printf("\tWarning!Consecutive use of operator!\n");par_warn++; $$ = ($1 >= $4) ? 1 : 0;}
        |float_expr LESS_EQ LESS_EQ float_expr			{printf("\tWarning!Consecutive use of operator!\n");par_warn++;$$ = ($1 <= $4) ? 1 : 0; }
        |float_expr EQUAL EQUAL float_expr			    {printf("\tWarning!Consecutive use of operator!\n");par_warn++; $$ = ($1 == $4) ? 1 : 0;}
        |float_expr NOT_EQUAL NOT_EQUAL float_expr		{printf("\tWarning!Consecutive use of operator!\n");par_warn++; $$ = ($1 != $4) ? 1 : 0;}
		;
string_expr:
		BINARY										{ $$ = $1; correct_words++; }
		| IMAGINARY									{ $$ = $1; correct_words++; }
		| IDENTIFIER								{ $$ = $1; correct_words++; }
		| IDENTIFIER IDENTIFIER						{ printf("\tWarning:Name with space!\n"); par_warn++; }
		| IDENTIFIER ASSIGN string_expr 			{ $$ = $3; correct_words++; }
		| IDENTIFIER ASSIGN dec_expr 				{ $$ = int_to_string($3); correct_words++; }
		| IDENTIFIER ASSIGN float_expr 				{ $$ = float_to_string($3); correct_words++; }
		| STRING									{ $$ = $1; correct_words++; }
		| KEYWORD									{ $$ = $1; correct_words++; }
		| PRINT LEFT_PAREN STRING RIGHT_PAREN  	 	{ $$ = $3; correct_words+=3; }
		| PRINT LEFT_PAREN DECIMAL RIGHT_PAREN  	{ $$ = int_to_string($3); correct_words+=3; }	
		| PRINT LEFT_PAREN FLOAT RIGHT_PAREN   		{ $$ = float_to_string($3); correct_words+=3; }
		| PRINT LEFT_PAREN IDENTIFIER RIGHT_PAREN   { $$ = $3; correct_words+=3; }
		| PRINT LEFT_PAREN BINARY RIGHT_PAREN   	{ $$ = $3; correct_words+=3; }
		| PRINT LEFT_PAREN IMAGINARY RIGHT_PAREN   	{ $$ = $3; correct_words+=3; }
		| PRINT LEFT_PAREN LS_BRACKET list_types RS_BRACKET RIGHT_PAREN	{ $$ = $4; correct_words+=5; }
		| PRINT LEFT_PAREN LEFT_PAREN list_types RIGHT_PAREN RIGHT_PAREN	{ $$ = $4; correct_words+=5; }
		;
list_expr:
		LS_BRACKET list_types RS_BRACKET		{ $$ = $2; correct_words+=2; }
		| LEFT_PAREN list_types RIGHT_PAREN		{ $$ = $2; correct_words+=2; }
		| LS_BRACKET list_types RS_BRACKET PLUS LS_BRACKET list_types RS_BRACKET		{ $$ = concatWithComma($2, $6); correct_words+=5; }
		| LEFT_PAREN list_types RIGHT_PAREN PLUS LEFT_PAREN list_types RIGHT_PAREN		{ $$ = concatWithComma($2, $6); correct_words+=5; }
		;
/* Χειρισμός λιστών και πλειάδων με string */
list_types:
		STRING			{ $$ = strdup($1); correct_words++; }
		| list_types COMMA STRING 
		{
			size_t list_len = strlen($1);
			size_t elem_len = strlen($3);
			$$ = malloc((list_len + 2 + elem_len) * sizeof(char));
			strcpy($$, $1);
			strcat($$, ", ");
			strcat($$, $3);
			free($1);
		}
		| DECIMAL		{ $$ = int_to_string($1); correct_words++; }
		| list_types COMMA DECIMAL 
		{
			char* str = int_to_string($3);
			size_t list_len = strlen($1);
			size_t elem_len = strlen(str);
			$$ = malloc((list_len + elem_len + 2) * sizeof(char));
			strcpy($$, $1);
			strcat($$, ", ");
			strcat($$, str);
			free($1);
			free(str);
		}
		| FLOAT			{ $$ = float_to_string($1); correct_words++; }
		| list_types COMMA FLOAT 
		{
			char* str = float_to_string($3);
			size_t list_len = strlen($1);
			size_t elem_len = strlen(str);
			$$ = malloc((list_len + elem_len + 2) * sizeof(char));
			strcpy($$, $1);
			strcat($$, ", ");
			strcat($$, str);
			free($1);
			free(str);
		}
		;

%%

/* Διαχείρηση συντακτικών λαθών με την yyerror */
void yyerror(const char* message) {
    fprintf(stderr, "Error at line %d: %s\n", par_warn, message);
}


/* Συνάρτηση main που διαχειρίζεται τα αρχεία input.txt-output.txt */
int main(int argc,char **argv){
		//yydebug = 1;
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


        int ret=yyparse();

		/* Παρουσίαση των λανθασμένων(errors/warnings) και σωστών λέξεων-εκφράσεων */
        if(ret==0){
            printf("\n\t\tBison->Parsing Succeeded.\n");
            fprintf(stderr,"Parsing completed with %d correct expression(s), %d correct words(s), %d error(s) and %d warning(s)\n",correct,correct_words,errors,par_warn);
			fprintf(yyout,"\nParsing completed with : \n");
			fprintf(yyout,"\nCorrect expression(s) : %d\n",correct);
			fprintf(yyout,"\nCorrect word(s) : %d\n",correct_words);
			fprintf(yyout,"\nWarning(s) : %d\n",par_warn);
			fprintf(yyout,"\nError(s) : %d\n",errors);
            printf("\n");
        }else{
            printf("\t\tBison->Parsing Failed");
			fprintf(yyout,"\t\tBison->Parsing Failed");
        }

       return 0;
}
